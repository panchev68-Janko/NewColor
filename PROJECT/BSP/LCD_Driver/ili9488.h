
#define LCD_WIDTH 480
#define LCD_HEIGHT 320

extern uint16_t pic[];
void swap (uint32_t x,uint32_t y);
void Write_Data_U16(uint16_t dat);
void Write_Cmd(uint16_t CMD);
void ili9488_Initial(void);
void MemoryAccessControl (unsigned char access);
void BLOCK_FULL(uint16_t xs, uint16_t xe, uint16_t ys, uint16_t ye, uint16_t color);
void LCD_SetWindow_Write(unsigned int xs,unsigned int xe,unsigned int ys,unsigned int ye);
size_t SetWindow (uint16_t X, uint16_t Y, uint16_t W, uint16_t H);
void SetPositionPixel(unsigned int x,unsigned int y);
void SetPixel (uint16_t x,uint16_t y, uint32_t color);
void SetPartial (unsigned int Ystart, unsigned int Yend);
void VerticalScrolling (unsigned int TFA, unsigned int VSA, unsigned int BFA);
void VerticalScrollingStartAddress (unsigned int address);
void Brightness (unsigned char brightness);
void ClearScreen(unsigned int bColor);
void LCD_FULL(unsigned int bColor);
void DrawObject( uint16_t *p_src, size_t size);
 
   

void DrawPic (uint16_t X, uint16_t Y, uint16_t W, uint16_t H, uint16_t *pic);
void drawFastVLine(int16_t x, int16_t y, int16_t h,uint16_t color);
void drawFastHLine(int16_t x, int16_t y, int16_t w,uint32_t color) ;
void DrawRect (int16_t x, int16_t y, int16_t w, int16_t h,	uint32_t color) ;
void fillRect(int16_t x, int16_t y, int16_t w, int16_t h,	uint32_t color);
void fillRectUp(int16_t x, int16_t y, int16_t w, int16_t h,	uint32_t color);
void fillRectUpStep(int16_t x, int16_t y, int16_t w, int16_t h,uint8_t Step, uint32_t foreground,uint32_t background) ;
void fillRectUpStepLimit(int16_t x, int16_t y, int16_t w, int16_t h,uint8_t Step, uint16_t Limit, uint32_t foreground,uint32_t LimitForeground, uint32_t background)  ;
void fillRectBar(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t limit,	uint32_t color1, uint32_t color2);
void drawCircle(int16_t x0, int16_t y0, int16_t r,uint16_t color);
void drawCircleHelper( int16_t x0, int16_t y0,int16_t r, uint8_t cornername, uint16_t color) ;
void fillCircle(int16_t x0, int16_t y0, int16_t r,uint16_t color);
void fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color);
void drawLine(int16_t x0, int16_t y0,	int16_t x1, int16_t y1, uint16_t color);
void Draw_line(
                uint32_t color,
                int32_t x0, int32_t y0,
                int32_t x1, int32_t y1,
                uint32_t line_thickness,
                uint32_t line_stile
               );
void line_fast(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint32_t color);
void drawRoundRect(int16_t x, int16_t y, int16_t w,  int16_t h, int16_t r, uint16_t color);
void drawTriangle(int16_t x0, int16_t y0,int16_t x1, int16_t y1,int16_t x2, int16_t y2, uint16_t color);
void fillTriangle ( int16_t x0, int16_t y0,int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) ;  //not work
void fillTriangle1(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t x3,uint16_t y3, uint32_t c);  //work
//void DrawBar(uint16_t bottomX, uint16_t bottomY, uint16_t maxHeight, uint16_t maxValue, float value, uint16_t foreground, uint16_t background) ;
//void DrawBarSector (int16_t x, int16_t y, int16_t w, int16_t h, uint32_t foreground, uint32_t background);
//void DrawBigBar(uint16_t bottomX, uint16_t bottomY, uint8_t Width, uint16_t Height,uint16_t limit, float value, uint16_t foreground, uint16_t background, uint16_t backgroundlimit);
void DispRGBGray(void);



//==============================================================================
extern uint16_t Buffer[14400];
void MallocBuff (uint16_t *Buff,uint16_t w, uint16_t h);
void FreeBuff (uint16_t *Buff);
void DefineBuff (uint16_t w, uint16_t h);
void SetPixelBuff (uint16_t *Buff,uint16_t x,uint16_t y, uint16_t color);
void Draw_Circle_Buff(uint16_t *Buff,int16_t x0, int16_t y0, int16_t r,uint16_t color) ;
void Draw_Line_Buff(uint16_t *Buff, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint32_t color);
void lcd_hline_Buff(uint16_t *Buff,uint16_t x1, uint16_t x2, uint16_t y, uint32_t color) ;
void Fill_Triangle_Buff(uint16_t *Buff,uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t x3,uint16_t y3, uint32_t c) ;
//==============================================================================

//void ili9488_Initial(void);
//void Write_Cmd_Data(uint16_t DAT);
//void Write_Cmd(uint16_t CMD);
//void Write_Data(unsigned char DH,unsigned char DL);
//void delayms(unsigned int tt);
//void  Write_Data_U16(uint16_t dat);
//void LCD_SetPos(unsigned int xs,unsigned int xe,unsigned int ys,unsigned int ye);
//void ClearScreen(unsigned int bColor);
//void LCD_FULL(unsigned int i);
//void BLOCK_FULL(uint16_t xs, uint16_t xe, uint16_t ys, uint16_t ye, uint16_t color);
//
//void MemoryAccessControl (unsigned char access);
// Color definitions
#define ILI9488_BLACK       0x0000      /*   0,   0,   0 */
#define ILI9488_NAVY        0x000F      /*   0,   0, 128 */
#define ILI9488_DARKGREEN   0x03E0      /*   0, 128,   0 */
#define ILI9488_DARKCYAN    0x03EF      /*   0, 128, 128 */
#define ILI9488_MAROON      0x7800      /* 128,   0,   0 */
#define ILI9488_PURPLE      0x780F      /* 128,   0, 128 */
#define ILI9488_OLIVE       0x7BE0      /* 128, 128,   0 */
#define ILI9488_LIGHTGREY   0xC618      /* 192, 192, 192 */
#define ILI9488_DARKGREY    0x7BEF      /* 128, 128, 128 */
#define ILI9488_BLUE        0x001F      /*   0,   0, 255 */
#define ILI9488_GREEN       0x07E0      /*   0, 255,   0 */
#define ILI9488_CYAN        0x07FF      /*   0, 255, 255 */
#define ILI9488_RED         0xF800      /* 255,   0,   0 */
#define ILI9488_MAGENTA     0xF81F      /* 255,   0, 255 */
#define ILI9488_YELLOW      0xFFE0      /* 255, 255,   0 */
#define ILI9488_WHITE       0xFFFF      /* 255, 255, 255 */
#define ILI9488_ORANGE      0xFD20      /* 255, 165,   0 */
#define ILI9488_GREENYELLOW 0xAFE5      /* 173, 255,  47 */
#define ILI9488_PINK        0xF81F
