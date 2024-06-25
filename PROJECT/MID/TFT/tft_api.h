/**
********************************************************************************
    @file    tft_api.h
    @brief   tft_api.h Header
    @author  Bobby 
    @version 1
    @date    12.12.2018
********************************************************************************
*/
#pragma once
#include "dma.h"

#define MaxBuffSize             150000 //144000 
#include "tft_colors_typedef.h"

typedef uint16_t Color_t;
void TFT_SetTextColor (Color_t foreground,Color_t background);
void InitFont (uint8_t *CurFont);
uint8_t FontWidht (void);
uint16_t StrWidth (uint8_t* string);
uint8_t FontHeight (void);
void TFT_SetTextXY (uint32_t x, uint32_t y);
void TFT_SetTextX (uint32_t x);
void TFT_SetTextY (uint32_t y);
uint32_t GetTextX (void);
uint32_t GetTextY (void);
void TFT_NewLine ();
void TFT_PutChar (uint8_t ch) ;
void TFT_PrintString (uint8_t* string);
void TFT_PrintString_Centred (uint16_t Y, uint8_t* string);
void TFT_PrintString_Centret_Win_ByX (uint16_t Xwin, uint16_t Ywin, uint16_t Wwin, uint16_t Hwin, 
                                  uint16_t Y, uint8_t *string);
void DrawPicFromIntFlash (DMA_HandleTypeDef *hdma,uint16_t StartX, uint16_t StartY, uint16_t width, uint16_t height, uint16_t *pic);

void DrawColorFromOneBitPic (uint16_t Xstart, uint16_t Ystart, uint16_t W, uint16_t H, uint16_t Fcolor, uint16_t Bcolor, uint8_t *PicOneBit);
void Draw2ColorFromOneBitPic (uint16_t Xstart, uint16_t Ystart, uint16_t W, uint16_t H, 
                              uint16_t Fcolor1, uint16_t Fcolor2, uint16_t Bcolor, uint8_t *PicOneBit1, uint8_t *PicOneBit2);
void DrawColorFromOneBitPicFromFlash (uint16_t Xstart, uint16_t Ystart, uint16_t W, uint16_t H, uint16_t Fcolor, uint16_t Bcolor, uint32_t start_addr);
/* End Of File */
