/**
********************************************************************************
    @file    tft_api.c
    @brief   tft_api.c Source Code
    @author  Bobby
    @version 1
    @date    12.12.2018
********************************************************************************
*/
#include "FreeRTOS.h"
#include "task.h"
#include "dma.h"
#include "fsmc.h"
#include "tft_api.h"
#include "ili9488.h"

//#include "SST25FlashDrv.h"

uint8_t *pFont;


__packed struct SRawFontHeader
{
    uint8_t FONT_WIDTH;               ///< Char Width (if 0 font is proporcional)
    uint8_t FONT_HEIGHT;              ///< Font Height
    uint8_t FONT_FST_CHAR;            ///< First character
    uint8_t FONT_CHAR_NUM;            ///< Number of characters in font
    uint8_t FONT_CHAR_FACE_HANDLER;   //offcet of first char
    uint32_t StartPos;
    uint16_t NEW_LINE_Y;
    bool proportional;
}Header;



static uint32_t _Text_X_Set,_Text_X,_Text_Y;

void TFT_SetTextXY (uint32_t x, uint32_t y)
{
    _Text_X_Set = _Text_X = x;
    _Text_Y = y;
};

void TFT_SetTextX (uint32_t x)
{
    _Text_X_Set = _Text_X = x;
};
void TFT_SetTextY (uint32_t y)
{
    _Text_Y = y;
};

uint32_t GetTextX (void)
{
  return _Text_X;
}

uint32_t GetTextY (void)
{
  return _Text_Y;
}

#define LCD_WIDTH 480
#define LCD_HEIGHT 320
//#define NEW_LINE_Y 20   //FONT_WIDTH*FontScale +???

#define FONT_CHAR_OFFSET 1
Color_t Foreground = 0xffff;
Color_t Background = 0x0;


Color_t _FaceBuf[ 75 * 75 ]; // max char size 55x55


void TFT_SetTextColor (Color_t foreground,Color_t background)
{
    Foreground = foreground;
    Background=background;
}

void InitFont (uint8_t *CurFont)
{
  pFont=CurFont;
  Header.FONT_WIDTH=pFont[0];
  Header.FONT_HEIGHT=pFont[1];
  Header.FONT_FST_CHAR=pFont[2];
  Header.FONT_CHAR_NUM=pFont[3];
  Header.FONT_CHAR_FACE_HANDLER=4;
  Header.NEW_LINE_Y= Header.FONT_WIDTH+(Header.FONT_WIDTH/10)+1;
  if (!Header.FONT_WIDTH) 
  {
    Header.proportional=true;
  }
  else 
  {
    Header.proportional=false;
  }
}

uint8_t FontWidht (void)
{
  return Header.FONT_WIDTH;
}

uint16_t StrWidth (uint8_t* string)
{
  uint16_t ret=0;
  uint8_t TempChar;
  for (uint32_t i=0 ;string[i]!=0;i++) 
  {
    if (Header.proportional)
    {
      TempChar=string[i]-pFont[2]+4;
      //ret+=pFont[string[i]-0x20+4 ];
      ret+=pFont[TempChar]+1;
    }
    else
    {
      ret+=Header.FONT_WIDTH;;
    }
  }
  return ret;
}

uint8_t FontHeight (void)
{
  return Header.FONT_HEIGHT;
}

void TFT_PutChar (uint8_t ch) 
{
  static uint32_t font_widht_in_bytes;
  static uint8_t i;
  
    if (_Text_Y + Header.FONT_HEIGHT >LCD_HEIGHT) return ;
    if (_Text_X + Header.FONT_WIDTH >=LCD_WIDTH) TFT_NewLine();
            
    if (ch <Header.FONT_FST_CHAR) return;
    ch -=  Header.FONT_FST_CHAR;
    if (ch >=Header.FONT_CHAR_NUM) return;
    
    if (Header.proportional)
    {
      Header.FONT_WIDTH=pFont[ch +4];
      Header.FONT_CHAR_FACE_HANDLER+=Header.FONT_CHAR_NUM;
      Header.FONT_CHAR_FACE_HANDLER++;
      font_widht_in_bytes = (Header.FONT_WIDTH+7)/8;
      Header.StartPos=4+Header.FONT_CHAR_NUM;  
      for (i=0;i<ch;i++)
      {
        Header.StartPos+=((pFont[i+4]+7)/8)*Header.FONT_HEIGHT;
      }
    }
    else
    {
      font_widht_in_bytes = (Header.FONT_WIDTH+7)/8;
      Header.StartPos=Header.FONT_CHAR_FACE_HANDLER + (ch*font_widht_in_bytes * Header.FONT_HEIGHT);
    }
    
    uint16_t* p_dst = _FaceBuf;
    for (uint32_t y = 0 ; y< Header.FONT_HEIGHT ;y++)
    {
        for (uint32_t x = 0 ; x < Header.FONT_WIDTH ;x++)
        {
          *(p_dst++) = ((pFont[Header.StartPos + (x / 8)]) & (1<<(x % 8))) ? Foreground: Background;
        }
        Header.StartPos+=font_widht_in_bytes;
    }
    DrawObject((uint16_t *)_FaceBuf , SetWindow (_Text_X,_Text_Y,Header.FONT_WIDTH-1,Header.FONT_HEIGHT-1));
    
    _Text_X+=Header.FONT_WIDTH + FONT_CHAR_OFFSET;

}

uint8_t *TFT_PrintStringInBuff (uint8_t *buff, uint16_t w, uint16_t h,const char *string, int16_t Xpos, int16_t Ypos, uint32_t color)
{
  uint8_t *ret;
  uint16_t *TempBuff=NULL;
  uint32_t size=w*h;
  //uint8_t Char_Height=Header.FONT_HEIGHT;
  uint8_t font_widht_in_bytes;
  uint16_t NewXpos=Xpos;
  
  DefineBuff(w,h);
  TempBuff=pvPortMalloc(size*2);
  memcpy(TempBuff,buff,size*2);
  ret=buff;
  for (uint8_t i=0 ;string[i]!=0;i++)
  {
     if (Header.proportional)
      {
        Header.FONT_WIDTH=pFont[string[i] +4];
        Header.FONT_CHAR_FACE_HANDLER+=Header.FONT_CHAR_NUM;
        Header.FONT_CHAR_FACE_HANDLER++;
        font_widht_in_bytes = (Header.FONT_WIDTH+7)/8;
        Header.StartPos=4+Header.FONT_CHAR_NUM;  
        for (uint8_t j=0;j<string[i];j++)
        {
          Header.StartPos+=((pFont[j+4]+7)/8)*Header.FONT_HEIGHT;
        }
      }
      else
      {
        font_widht_in_bytes = (Header.FONT_WIDTH+7)/8;
        Header.StartPos=Header.FONT_CHAR_FACE_HANDLER + (string[i]*font_widht_in_bytes * Header.FONT_HEIGHT);
      }
    if ((NewXpos+font_widht_in_bytes)<0)           //izvan bufera
    {}
    else
    {
      
    }
  }
  
  return ret;
}

void TFT_PrintString (uint8_t* string)
{
    for (uint32_t i=0 ;string[i]!=0;i++) TFT_PutChar(string[i]);
}

void TFT_PrintString_Centred (uint16_t Y, uint8_t *string)
{
  uint16_t Xpos,TextLenght;
  TextLenght=StrWidth (string);
  Xpos=(LCD_WIDTH-TextLenght)/2;
  TFT_SetTextXY(Xpos,Y);
  TFT_PrintString (string);
}

void TFT_PrintString_Centret_Win_ByX (uint16_t Xwin, uint16_t Ywin, uint16_t Wwin, uint16_t Hwin, 
                                  uint16_t Y, uint8_t *string)
{
  uint16_t Xpos,TextLenght;
  TextLenght=StrWidth (string);
  Xpos=Xwin+(Wwin-TextLenght)/2;
  TFT_SetTextXY(Xpos,Ywin+Y);
  TFT_PrintString (string);
}

void TFT_NewLine ()
{
    _Text_X = _Text_X_Set;
    _Text_Y += Header.NEW_LINE_Y;
}

void DrawPicFromIntFlash (DMA_HandleTypeDef *hdma,uint16_t StartX, uint16_t StartY, uint16_t width, uint16_t height, uint16_t *pic)
{
//  SetWindow (StartX,StartY,width-1,height-1);
//  //HAL_DMA_Start_IT(hdma,*pic,(uint32_t)&hsram1 ,width*height);
//  HAL_DMA_Start(hdma,*pic,(uint32_t)&hsram1 ,width*height);
}

void DrawOneBitPic (DMA_HandleTypeDef *hdma,uint16_t StartX, uint16_t StartY, uint16_t width, uint16_t height, uint16_t *PicOneBit)
{
  //parwo TFT_SetTextColor (Color_t foreground,Color_t background)!!!!
  uint8_t *pic;
  uint32_t temp;
  SetWindow (StartX,StartY,width-1,height-1);

  temp=width*height*2;
 //pic = (char *) malloc(xlong*ylong);
  if(uxTaskGetNumberOfTasks())
        pic=pvPortMalloc(temp);
    else
        pic=malloc(temp);
  for (uint32_t x = 0 ; x < temp ;x++)
  {
    *(pic++) = ((PicOneBit[x / 8]) & (1<<(x % 8))) ? Foreground: Background;
  }
  //HAL_DMA_Start_IT(hdma,*pic,&hsram1 ,width*height);
  HAL_DMA_Start(hdma,(uint32_t)*pic,(uint32_t)&hsram1 ,width*height);
  if(uxTaskGetNumberOfTasks())
        vPortFree( pic );
    else
        free( pic );
}



void DrawColorFromOneBitPic (uint16_t Xstart, uint16_t Ystart, uint16_t W, uint16_t H, uint16_t Fcolor, uint16_t Bcolor, uint8_t *PicOneBit)
{
  uint16_t Y0=Ystart,Htemp=H;
  uint32_t size=W*H;
  uint16_t *p_dst=NULL,*ptemp,*ptemp1,z;
  static uint8_t i=0;
  uint8_t TempPic=*PicOneBit++;
  bool bigpic=true;

  if(uxTaskGetNumberOfTasks())
        p_dst=pvPortMalloc(size*2);
    else
        p_dst=malloc(size);
  ptemp1=p_dst;
  while (bigpic)
  {
    size=W*H;
    if (size>MaxBuffSize)
    {
      Htemp=MaxBuffSize/W;
      H-=Htemp;
      bigpic=true;
    }
    else 
    {
      bigpic=false;
    }
    size=Htemp*W;
    *p_dst=NULL;
    ptemp=p_dst;

    while (size)
    {
      z=(TempPic & (0x80>>(i % 8))) ? Fcolor: Bcolor;   //ako e obratno orientirana (TempPic & (1<<(i % 8))) ? Fcolor: Bcolor;
      *(p_dst++) = z;
      if(i<7) i++;
      else
      {
        i=0;
        TempPic=*PicOneBit++;
      }
      size--;
    }
    DrawPic (Xstart,Y0, W,Htemp,ptemp);
    Y0+=Htemp;
    Htemp=H;
  }
  
  if(uxTaskGetNumberOfTasks())
        vPortFree( ptemp1 );
    else
        free( p_dst );
}


void Draw2ColorFromOneBitPic (uint16_t Xstart, uint16_t Ystart, uint16_t W, uint16_t H, 
                              uint16_t Fcolor1, uint16_t Fcolor2, uint16_t Bcolor, uint8_t *PicOneBit1, uint8_t *PicOneBit2)
{
  uint16_t Y0=Ystart,Htemp=H;
  uint32_t size=W*H;
  uint16_t *p_dst=NULL,*ptemp,*ptemp1,z;
  static uint8_t i=0;
  uint8_t TempPic1=*PicOneBit1++,TempPic2=*PicOneBit2++;
  bool bigpic=true;

  if(uxTaskGetNumberOfTasks())
        p_dst=pvPortMalloc(size*2);
    else
        p_dst=malloc(size);
  ptemp1=p_dst;
  while (bigpic)
  {
    size=W*H;
    if (size>MaxBuffSize)
    {
      Htemp=MaxBuffSize/W;
      H-=Htemp;
      bigpic=true;
    }
    else 
    {
      bigpic=false;
    }
    size=Htemp*W;
    *p_dst=NULL;
    ptemp=p_dst;

    while (size)
    {
      if(TempPic1 & (0x80>>(i % 8))) z=Fcolor2;
      else
      z=(TempPic1 & (0x80>>(i % 8))) ? Fcolor1: Bcolor;   //ako e obratno orientirana (TempPic & (1<<(i % 8))) ? Fcolor: Bcolor;
      *(p_dst++) = z;
      if(i<7) i++;
      else
      {
        i=0;
        TempPic1=*PicOneBit1++;
        TempPic2=*PicOneBit2++;
      }
      size--;
    }
    DrawPic (Xstart,Y0, W,Htemp,ptemp);
    Y0+=Htemp;
    Htemp=H;
  }
  
  if(uxTaskGetNumberOfTasks())
        vPortFree( ptemp1 );
    else
        free( p_dst );
}

void DrawColorFromOneBitPicFromFlash (uint16_t Xstart, uint16_t Ystart, uint16_t W, uint16_t H, uint16_t Fcolor, uint16_t Bcolor, uint32_t start_addr)
{
//  uint16_t Y0=Ystart,Htemp=H;
//  uint32_t size=W*H;
//  uint16_t *p_dst=NULL,*ptemp,*ptemp1,z;
//  static uint8_t i=0;
//  bool bigpic=true;
//  uint8_t TempPic=SSTxReadByte(start_addr++);
//  
//  if(uxTaskGetNumberOfTasks())
//        p_dst=pvPortMalloc(size*2);
//    else
//        p_dst=malloc(size);
//  ptemp1=p_dst;
//  while (bigpic)
//  {
//    size=W*H;
//    if (size>MaxBuffSize)
//    {
//      Htemp=MaxBuffSize/W;
//      H-=Htemp;
//      bigpic=true;
//    }
//    else 
//    {
//      bigpic=false;
//    }
//    size=Htemp*W;
//    *p_dst=NULL;
//    ptemp=p_dst;
//
//    while (size)
//    {
//      z=(TempPic & (0x80>>(i % 8))) ? Fcolor: Bcolor;   //ako e obratno orientirana z=(TempPic & (1<<(i % 8))) ? Fcolor: Bcolor;
//      *(p_dst++) = z;
//      if(i<7) i++;
//      else
//      {
//        i=0;
//        TempPic=SSTxReadByte(start_addr++);
//      }
//      size--;
//    }
//    DrawPic (Xstart,Y0, W,Htemp,ptemp);
//    Y0+=Htemp;
//    Htemp=H;
//  }
//  
//  if(uxTaskGetNumberOfTasks())
//        vPortFree( ptemp1 );
//    else
//        free( p_dst );

}


//bool DrawPicInWindow (uint16_t Xwin, uint16_t Ywin, uint16_t Wwin, uint16_t Hwin, 
//                      int16_t Xpic, int16_t Ypic, uint16_t Wpic, uint16_t Hpic, 
//                      uint16_t Fcolor, uint16_t Bcolor, uint8_t *pic) //ili uint16_t pic ????
//{
//  uint16_t Xreal,Yreal,Wreal,Hreal,X0=Xpic, Y0=Ypic,H0=Hpic;
//  uint32_t size=0,size1=0;
//  uint16_t *p_dst=NULL,*ptemp,*ptemp1,z;
//  uint8_t i,j;
//  uint8_t TempPic=*pic++;
//  bool bigpic=true;
//  
//  if (Xpic>Xwin) return false;
//  if (Ypic>Ywin) return false;
//  if (Xpic<Xwin) Xreal=Xwin;
//  else Xreal=Xpic;
//  if (Ypic<Ywin) Yreal=Ywin;
//  else Yreal=Ypic;
//  if ((Xpic+Wpic)>(Xwin+Wwin)) Wreal=(Xwin+Wwin)-Xpic;
//  else Wreal=Wpic;
//  if ((Ypic+Hpic)>(Ywin+Hwin)) Hreal=(Ywin+Hwin)-Ypic;
//  else Hreal=Hpic;
//  size=Wreal*Hreal;
//  if(uxTaskGetNumberOfTasks())
//    p_dst=pvPortMalloc(size*2);
//  else
//    p_dst=malloc(size);
//  ptemp1=p_dst;
//  
//  while (bigpic)
//  {
//    for (i=0;i<Wpic;i++)
//    {
//      for (j=0;j<Hpic;j++)
//      {
//        if ((i>Xreal) && (i<Xreal+Wreal))
//        {
//          if ((j>Yreal) && (j<Yreal+Hreal))
//          {
//            z=(TempPic1 & (0x80>>(i % 8))) ? Fcolor: Bcolor;   //ako e obratno orientirana (TempPic & (1<<(i % 8))) ? Fcolor: Bcolor;
//            *(p_dst++) = z;
//            size1++;
//            if (size1>size)
//            {}
//          }
//        }
//      }
//    }
//    size=Wreal*Hreal;
//    if (size>MaxBuffSize)
//    {
//      bigpic=true;
//    }
//    else
//    {
//      bigpic=false;
//    }
//  }
//  
//  if(uxTaskGetNumberOfTasks())
//    vPortFree( ptemp1 );
//  else
//    free( p_dst );
//}
/* End Of File */
