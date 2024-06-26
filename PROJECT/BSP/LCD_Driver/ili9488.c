#include "ili9488.h"
#include "cmsis_os.h"
#include "fsmc.h"
#include "tft_colors_typedef.h"

// #include "dma.h"

// #define LCD_WIDTH 480
// #define LCD_HEIGHT 320
//---------- DA SE DEFINEIRA ---------------------------------------------------
#define ResetPIN        LCD_Reset_Pin
#define ResetPORT       LCD_Reset_GPIO_Port
#define BackLightPIN    LCD_Led_Pin
#define BackLightPORT   LCD_Led_GPIO_Port
#define COMMAND_POINTER 0x60000000
#define DATA_POINTER    0x60020000
//------------------------------------------------------------------------------

static uint32_t * LCD_CMD  = (uint32_t *) COMMAND_POINTER;
static uint32_t * LCD_DATA = (uint32_t *) DATA_POINTER;

// Swap two bytes
#define SWAP(x, y)       \
    do {                 \
        (x) = (x) ^ (y); \
        (y) = (x) ^ (y); \
        (x) = (x) ^ (y); \
    } while (0)

void swap (uint32_t x, uint32_t y)
{
    uint32_t temp;
    temp = x;
    x    = y;
    y    = temp;
}

//==============================================================
// write  data word
void Write_Data_U16 (uint16_t dat)
{
    HAL_SRAM_Write_16b (&hsram1, LCD_DATA, &dat, 1);
}

//=============================================================
// write command
void Write_Cmd (uint16_t CMD)
{
    HAL_SRAM_Write_16b (&hsram1, LCD_CMD, &CMD, 1);
}

//============================================================
// delay
// void delayms(unsigned int count)
//{
//    int i,j;
//    for(i=0;i<count;i++)
//       {
//	     for(j=0;j<1000;j++);
//       }
//}
//=============================================================
// lcd initial
void ili9488_Initial (void)
{
    HAL_GPIO_WritePin (ResetPORT, ResetPIN, GPIO_PIN_SET);        // RESET=1
    // osDelay(5);
    HAL_Delay (5);
    HAL_GPIO_WritePin (ResetPORT, ResetPIN, GPIO_PIN_RESET);        // RESET=0
    // osDelay(10);
    HAL_Delay (10);
    HAL_GPIO_WritePin (ResetPORT, ResetPIN, GPIO_PIN_SET);        // RESET=1
    // delayms(120);
    HAL_Delay (120);

    // PGAMCTRL(Positive Gamma Control)
    Write_Cmd (0xE0);
    Write_Data_U16 (0x00);
    Write_Data_U16 (0x03);
    Write_Data_U16 (0x09);
    Write_Data_U16 (0x08);
    Write_Data_U16 (0x16);
    Write_Data_U16 (0x0A);
    Write_Data_U16 (0x3F);
    Write_Data_U16 (0x78);
    Write_Data_U16 (0x4C);
    Write_Data_U16 (0x09);
    Write_Data_U16 (0x0A);
    Write_Data_U16 (0x08);
    Write_Data_U16 (0x16);
    Write_Data_U16 (0x1A);
    Write_Data_U16 (0x0F);

    // NGAMCTRL(Negative Gamma Control)
    Write_Cmd (0XE1);
    Write_Data_U16 (0x00);
    Write_Data_U16 (0x16);
    Write_Data_U16 (0x19);
    Write_Data_U16 (0x03);
    Write_Data_U16 (0x0F);
    Write_Data_U16 (0x05);
    Write_Data_U16 (0x32);
    Write_Data_U16 (0x45);
    Write_Data_U16 (0x46);
    Write_Data_U16 (0x04);
    Write_Data_U16 (0x0E);
    Write_Data_U16 (0x0D);
    Write_Data_U16 (0x35);
    Write_Data_U16 (0x37);
    Write_Data_U16 (0x0F);

    Write_Cmd (0XC0);             // Power Control 1
    Write_Data_U16 (0x17);        // Vreg1out
    Write_Data_U16 (0x15);        // Verg2out

    Write_Cmd (0xC1);             // Power Control 2
    Write_Data_U16 (0x41);        // VGH,VGL

    Write_Cmd (0xC5);        // Power Control 3
    Write_Data_U16 (0x00);
    Write_Data_U16 (0x12);        // Vcom
    Write_Data_U16 (0x80);

    Write_Cmd (0x36);        // Memory Access
    Write_Data_U16 (0x48);

    Write_Cmd (0x3A);             // Interface Pixel Format
    Write_Data_U16 (0x55);        // 16 bit

    Write_Cmd (0XB0);        // Interface Mode Control
    Write_Data_U16 (0x00);

    Write_Cmd (0xB1);             // Frame rate
    Write_Data_U16 (0xA0);        // 60Hz

    Write_Cmd (0xB4);             // Display Inversion Control
    Write_Data_U16 (0x02);        // 2-dot

    Write_Cmd (0XB6);        // Display Function Control  RGB/MCU Interface Control

    Write_Data_U16 (0x02);        // MCU
    Write_Data_U16 (0x02);        // Source,Gate scan dieection

    Write_Cmd (0XE9);             // Set Image Functio
    Write_Data_U16 (0x00);        // Disable 24 bit data

    Write_Cmd (0xF7);        // Adjust Control
    Write_Data_U16 (0xA9);
    Write_Data_U16 (0x51);
    Write_Data_U16 (0x2C);
    Write_Data_U16 (0x82);        // D7 stream, loose

    Write_Cmd (0x11);        // Sleep out
    HAL_Delay (120);
    Write_Cmd (0x29);

    MemoryAccessControl (0x28);        // rotate 90 grad
    HAL_GPIO_WritePin (BackLightPORT, BackLightPIN, GPIO_PIN_SET);
}

//============================================================
// Memory Access Control
// D7 MY ROW Adress Order  VERTICAL MIRROR
// D6 MX Column Adress Order   HORIZONTAL MIRROR
// D5 MV Row/Column ezchange
// D4 ML Vertical Refresh Order
// D3 BGR 0-RGB, 1-BGR
// D2 MH Horizontal refresh Order
// D1 XX
// D0 XX
void MemoryAccessControl (unsigned char access)
{
    Write_Cmd (0x36);
    Write_Data_U16 (access);
    HAL_Delay (100);
}

//============================================================
// show Box
void BLOCK_FULL (uint16_t xs, uint16_t xe, uint16_t ys, uint16_t ye, uint16_t color)
{
    uint32_t i, j;
    LCD_SetWindow_Write (xs, xe, ys, ye);
    j = (xe - xs + 1) * (ye - ys + 1);
    for (i = 0; i < j; i++)
    {
        Write_Data_U16 (color);
    }
}

//===============================================================
// SetPos and Write
void LCD_SetWindow_Write (unsigned int xs, unsigned int xe, unsigned int ys, unsigned int ye)
{
    Write_Cmd (0x2A);
    Write_Data_U16 (xs >> 8);
    Write_Data_U16 (xs & 0xff);
    Write_Data_U16 (xe >> 8);
    Write_Data_U16 (xe & 0xff);
    Write_Cmd (0x2B);
    Write_Data_U16 (ys >> 8);
    Write_Data_U16 (ys & 0xff);
    Write_Data_U16 (ye >> 8);
    Write_Data_U16 (ye & 0xff);
    Write_Cmd (0x2C);        // write memory
    // Write_Cmd(0x3C);        //write memory CONTINUE
}

//===============================================================
// Set WINDOW
size_t SetWindow (uint16_t X, uint16_t Y, uint16_t W, uint16_t H)
{
    Write_Cmd (0x2A);
    Write_Data_U16 (X >> 8);
    Write_Data_U16 (X & 0xff);
    Write_Data_U16 ((X + W) >> 8);
    Write_Data_U16 ((X + W) & 0xff);
    Write_Cmd (0x2B);
    Write_Data_U16 (Y >> 8);
    Write_Data_U16 (Y & 0xff);
    Write_Data_U16 ((Y + H) >> 8);
    Write_Data_U16 ((Y + H) & 0xff);
    Write_Cmd (0x2C);
    return ((W + 1) * (H + 1));
}

//===============================================================
// Set Position Pixel
void SetPositionPixel (unsigned int x, unsigned int y)
{
    LCD_SetWindow_Write (x, x + 1, y, y + 1);
}

//===============================================================
// Set Pixel
void SetPixel (uint16_t x, uint16_t y, uint32_t color)
{
    LCD_SetWindow_Write (x, x + 1, y, y + 1);
    Write_Data_U16 (color);
}

//============================================================
// Partial Area
void SetPartial (unsigned int Ystart, unsigned int Yend)
{
    Write_Cmd (0x30);
    Write_Data_U16 (Ystart >> 8);
    Write_Data_U16 (Ystart & 0xff);
    Write_Data_U16 (Yend >> 8);
    Write_Data_U16 (Yend & 0xff);
    Write_Cmd (0x12);        // start Partial Mode
}

//============================================================
// Vertical Scrolling Definition

void VerticalScrolling (unsigned int TFA, unsigned int VSA, unsigned int BFA)
{
    Write_Cmd (0x33);
    Write_Data_U16 (TFA >> 8);
    Write_Data_U16 (TFA & 0xff);
    Write_Data_U16 (VSA >> 8);
    Write_Data_U16 (VSA & 0xff);
    Write_Data_U16 (BFA >> 8);
    Write_Data_U16 (BFA & 0xff);
}

//============================================================
// Vertical Scrolling Start address

void VerticalScrollingStartAddress (unsigned int address)
{
    Write_Cmd (0x37);
    Write_Data_U16 (address >> 8);
    Write_Data_U16 (address & 0xff);
}

//============================================================
// Change Brightnes

void Brightness (unsigned char brightness)
{
    Write_Cmd (0x51);
    Write_Data_U16 (brightness);
    Write_Cmd (0x53);
    Write_Data_U16 (0x2c);
}

//===============================================================
// all display one colour
void LCD_FULL (unsigned int bColor)
{
    unsigned int i, j;
    LCD_SetWindow_Write (0, LCD_WIDTH, 0, LCD_HEIGHT);
    for (i = 0; i < LCD_HEIGHT; i++)
    {
        for (j = 0; j < LCD_WIDTH; j++)
            Write_Data_U16 (bColor);
    }
}

//============================================================
// show Box
void DrawObject (uint16_t * p_src, size_t size)
{
    do
    {
        Write_Data_U16 (*p_src++);
        size--;

    } while (size > 0);
}

//============================================================
// Draw Pic
void DrawPic (uint16_t X, uint16_t Y, uint16_t W, uint16_t H, uint16_t * pic)
{
    uint16_t i, j;
    LCD_SetWindow_Write (X, X + W - 1, Y, Y + H - 1);

    for (i = 0; i < H; i++)
    {
        for (j = 0; j < W; j++)
        {
            Write_Data_U16 (*pic++);
        }
    }
    LCD_SetWindow_Write (0, LCD_WIDTH, 0, LCD_HEIGHT);
}

//============================================================
// draw fast VLINE
void drawFastVLine (int16_t x, int16_t y, int16_t h, uint16_t color)
{
    uint16_t i;
    // Rudimentary clipping
    if ((x >= LCD_WIDTH) || (y >= LCD_HEIGHT)) return;

    if ((y + h - 1) >= LCD_HEIGHT)
        h = LCD_HEIGHT - y;

    // DrawObject(color , SetWindow (x,y,x,y+h-1));
    if (h < 0)
    {
        LCD_SetWindow_Write (x, x, y + h - 1, y);
        for (i = (y + h - 1); i < y; i++)
        {
            Write_Data_U16 (color);
        }
    }
    else
    {
        LCD_SetWindow_Write (x, x, y, y + h - 1);
        for (i = y; i < (y + h - 1); i++)
        {
            Write_Data_U16 (color);
        }
    }
}

//============================================================
// draw fast HLINE
void drawFastHLine (int16_t x, int16_t y, int16_t w, uint32_t color)
{
    uint16_t i;
    // Rudimentary clipping
    if ((x >= LCD_WIDTH) || (y >= LCD_HEIGHT)) return;
    if ((x + w - 1) >= LCD_WIDTH) w = LCD_WIDTH - x;

    LCD_SetWindow_Write (x, x + w - 1, y, y);
    for (i = x; i < (x + w - 1); i++)
    {
        Write_Data_U16 (color);
    }
}

//============================================================
// Draw a rectangle
void DrawRect (int16_t x, int16_t y, int16_t w, int16_t h, uint32_t color)
{
    if (h > y) h = y;
    if (((x + w) >= LCD_WIDTH) || (y >= LCD_HEIGHT) || (w >= LCD_WIDTH)) return;
    if ((x + w - 1) >= LCD_WIDTH) w = LCD_WIDTH - x;
    if ((y + h - 1) >= LCD_HEIGHT) h = LCD_HEIGHT - y;
    drawFastVLine (x, y, h, color);
    drawFastVLine (x + w, y, h, color);
    drawFastHLine (x + 1, y - 1, w, color);
    if (h < 0) drawFastHLine (x + 1, y + h - 1, w, color);
    else drawFastHLine (x, y - h, w, color);
}

//============================================================
// fill a rectangle ot Y nadoly
void fillRect (int16_t x, int16_t y, int16_t w, int16_t h, uint32_t color)
{
    uint16_t i, j;
    // rudimentary clipping (drawChar w/big text requires this)
    if ((x >= LCD_WIDTH) || (y >= LCD_HEIGHT)) return;
    if ((x + w - 1) >= LCD_WIDTH) w = LCD_WIDTH - x;
    if ((y + h - 1) >= LCD_HEIGHT) h = LCD_HEIGHT - y;

    LCD_SetWindow_Write (x, x + w - 1, y, y + h);
    for (j = y; j < y + h; j++)
    {
        //      HAL_DMA_Start(&hdma_memtomem_dma2_stream0,color,(uint32_t)&hsram1,h-1);
        for (i = x; i < x + w; i++)
        {
            Write_Data_U16 (color);
        }
    }
}

//============================================================
// fill a rectangle from bottom to top ot Y nagore
void fillRectUp (int16_t x, int16_t y, int16_t w, int16_t h, uint32_t color)
{
    uint16_t i, j;
    // rudimentary clipping (drawChar w/big text requires this)
    if ((x >= LCD_WIDTH) || (y >= LCD_HEIGHT)) return;
    if ((x + w - 1) >= LCD_WIDTH) w = LCD_WIDTH - x;
    // if((y + h - 1) >= LCD_HEIGHT) h = LCD_HEIGHT - y;

    LCD_SetWindow_Write (x, x + w - 1, y - h, y);
    for (j = y - h; j < y; j++)
    {
        //      HAL_DMA_Start(&hdma_memtomem_dma2_stream0,color,(uint32_t)&hsram1,h-1);
        for (i = x; i < x + w; i++)
        {
            Write_Data_U16 (color);
        }
    }
}

//============================================================
// fill a rectangle from bottom to top ot Y nagore
void fillRectUpStep (int16_t x, int16_t y, int16_t w, int16_t h, uint8_t Step, uint32_t foreground, uint32_t background)
{
    int16_t i, j, k = 0;
    // rudimentary clipping (drawChar w/big text requires this)
    if ((x >= LCD_WIDTH) || (y >= LCD_HEIGHT)) return;
    if ((x + w - 1) >= LCD_WIDTH) w = LCD_WIDTH - x;
    // if((y + h - 1) >= LCD_HEIGHT) h = LCD_HEIGHT - y;
    h = h * Step;
    LCD_SetWindow_Write (x, x + w - 1, y - h, y);
    for (j = y - h; j < y - 1; j++)
    {
        //      HAL_DMA_Start(&hdma_memtomem_dma2_stream0,color,(uint32_t)&hsram1,h-1);
        if (k < (Step - 1))
        {
            for (i = x; i < x + w; i++) Write_Data_U16 (foreground);
            k++;
        }
        else
        {
            for (i = x; i < x + w; i++) Write_Data_U16 (background);
            k = 0;
        }
    }
}

//============================================================
// fill a rectangle from bottom to top ot Y nagore with limit color
void fillRectUpStepLimit (int16_t x, int16_t y, int16_t w, int16_t h, uint8_t Step, uint16_t Limit, uint32_t foreground, uint32_t LimitForeground, uint32_t background)
{
    int16_t i, j, k = 0;
    // rudimentary clipping (drawChar w/big text requires this)
    if ((x >= LCD_WIDTH) || (y >= LCD_HEIGHT)) return;
    if ((x + w - 1) >= LCD_WIDTH) w = LCD_WIDTH - x;
    // if((y + h - 1) >= LCD_HEIGHT) h = LCD_HEIGHT - y;
    h = h * Step;
    Limit *= Step;
    LCD_SetWindow_Write (x, x + w - 1, y - h, y);
    for (j = y - h; j < y - 1; j++)
    {
        //      HAL_DMA_Start(&hdma_memtomem_dma2_stream0,color,(uint32_t)&hsram1,h-1);
        if (k < (Step - 1))
        {
            if ((y - h) < Limit)
            {
                for (i = x; i < x + w; i++) Write_Data_U16 (LimitForeground);
            }
            else
            {
                for (i = x; i < x + w; i++) Write_Data_U16 (foreground);
            }
            k++;
        }
        else
        {
            for (i = x; i < x + w; i++) Write_Data_U16 (background);
            k = 0;
        }
    }
}

//============================================================
// fill a rectangle bar
void fillRectBar (int16_t x, int16_t y, int16_t w, int16_t h, uint16_t limit, uint32_t color1, uint32_t color2)
{
    uint16_t i, j, k;
    bool colback        = false;
    uint32_t foreground = color1;
    // rudimentary clipping (drawChar w/big text requires this)
    if ((x >= LCD_WIDTH) || (y >= LCD_HEIGHT)) return;
    if ((x + w - 1) >= LCD_WIDTH) w = LCD_WIDTH - x;
    if ((y + h - 1) >= LCD_HEIGHT) h = LCD_HEIGHT - y;

    if (h < 0)
    {
        LCD_SetWindow_Write (x, x + w, y + h - 1, y);
        for (j = y + h; j < y + 1; j++)
        {
            if (colback)
            {
                if (k < 5) k++;
                else
                {
                    k          = 0;
                    colback    = false;
                    foreground = 0;
                }
            }
            else
            {
                if (k < 2) k++;
                else
                {
                    k       = 0;
                    colback = true;
                    if (j < limit)
                        foreground = color2;
                    else foreground = color1;
                }
            }
            for (i = x; i < x + w + 1; i++)
            {
                Write_Data_U16 (foreground);
            }
        }
    }
    else
    {
        LCD_SetWindow_Write (x, x + w - 1, y, y + h - 1);
        for (i = x; i < x + w - 1; i++)
        {
            for (j = y; j < y + h - 1; j++)
            {
                Write_Data_U16 (color1);
            }
        }
    }
}

//============================================================
// Draw Circle
void drawCircle (int16_t x0, int16_t y0, int16_t r, uint16_t color)
{
    int16_t f     = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x     = 0;
    int16_t y     = r;

    SetPixel (x0, y0 + r, color);
    SetPixel (x0, y0 - r, color);
    SetPixel (x0 + r, y0, color);
    SetPixel (x0 - r, y0, color);

    while (x < y)
    {
        if (f >= 0)
        {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        SetPixel (x0 + x, y0 + y, color);
        SetPixel (x0 - x, y0 + y, color);
        SetPixel (x0 + x, y0 - y, color);
        SetPixel (x0 - x, y0 - y, color);
        SetPixel (x0 + y, y0 + x, color);
        SetPixel (x0 - y, y0 + x, color);
        SetPixel (x0 + y, y0 - x, color);
        SetPixel (x0 - y, y0 - x, color);
    }
}

//============================================================
// drawCircleHelper
void drawCircleHelper (int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint16_t color)
{
    int16_t f     = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x     = 0;
    int16_t y     = r;

    while (x < y)
    {
        if (f >= 0)
        {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;
        if (cornername & 0x4)
        {
            SetPixel (x0 + x, y0 + y, color);
            SetPixel (x0 + y, y0 + x, color);
        }
        if (cornername & 0x2)
        {
            SetPixel (x0 + x, y0 - y, color);
            SetPixel (x0 + y, y0 - x, color);
        }
        if (cornername & 0x8)
        {
            SetPixel (x0 - y, y0 + x, color);
            SetPixel (x0 - x, y0 + y, color);
        }
        if (cornername & 0x1)
        {
            SetPixel (x0 - y, y0 - x, color);
            SetPixel (x0 - x, y0 - y, color);
        }
    }
}

//============================================================
// draw full circle
void fillCircle (int16_t x0, int16_t y0, int16_t r, uint16_t color)
{
    drawFastVLine (x0, y0 - r, 2 * r + 1, color);
    fillCircleHelper (x0, y0, r, 3, 0, color);
}

//============================================================
// draw full circle Helper
// Used to do circles and roundrects
void fillCircleHelper (int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color)
{
    int16_t f     = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x     = 0;
    int16_t y     = r;

    while (x < y)
    {
        if (f >= 0)
        {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        if (cornername & 0x1)
        {
            drawFastVLine (x0 + x, y0 - y, 2 * y + 1 + delta, color);
            drawFastVLine (x0 + y, y0 - x, 2 * x + 1 + delta, color);
        }
        if (cornername & 0x2)
        {
            drawFastVLine (x0 - x, y0 - y, 2 * y + 1 + delta, color);
            drawFastVLine (x0 - y, y0 - x, 2 * x + 1 + delta, color);
        }
    }
}

//============================================================
// Draw Line
void drawLine (int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color)
{
    if (y0 == y1)
    {
        if (x1 > x0)
        {
            drawFastHLine (x0, y0, x1 - x0 + 1, color);
        }
        else if (x1 < x0)
        {
            drawFastHLine (x1, y0, x0 - x1 + 1, color);
        }
        else
        {
            SetPixel (x0, y0, color);
        }
        return;
    }
    else if (x0 == x1)
    {
        if (y1 > y0)
        {
            drawFastVLine (x0, y0, y1 - y0 + 1, color);
        }
        else
        {
            drawFastVLine (x0, y1, y0 - y1 + 1, color);
        }
        return;
    }

    bool steep = abs (y1 - y0) > abs (x1 - x0);
    if (steep)
    {
        swap (x0, y0);
        swap (x1, y1);
    }
    if (x0 > x1)
    {
        swap (x0, x1);
        swap (y0, y1);
    }

    int16_t dx, dy;
    dx = x1 - x0;
    dy = abs (y1 - y0);

    int16_t err = dx / 2;
    int16_t ystep;

    if (y0 < y1)
    {
        ystep = 1;
    }
    else
    {
        ystep = -1;
    }

    // beginSPITransaction();
    int16_t xbegin = x0;
    if (steep)
    {
        for (; x0 <= x1; x0++)
        {
            err -= dy;
            if (err < 0)
            {
                int16_t len = x0 - xbegin;
                if (len)
                {
                    drawFastVLine (y0, xbegin, len + 1, color);
                }
                else
                {
                    SetPixel (y0, x0, color);
                }
                xbegin = x0 + 1;
                y0 += ystep;
                err += dx;
            }
        }
        if (x0 > xbegin + 1)
        {
            drawFastVLine (y0, xbegin, x0 - xbegin, color);
        }
    }
    else
    {
        for (; x0 <= x1; x0++)
        {
            err -= dy;
            if (err < 0)
            {
                int16_t len = x0 - xbegin;
                if (len)
                {
                    drawFastHLine (xbegin, y0, len + 1, color);
                }
                else
                {
                    SetPixel (x0, y0, color);
                }
                xbegin = x0 + 1;
                y0 += ystep;
                err += dx;
            }
        }
        if (x0 > xbegin + 1)
        {
            drawFastHLine (xbegin, y0, x0 - xbegin, color);
        }
    }
    // writecommand_last(ILI9488_NOP);
    // endSPITransaction();
}

void line_fast (uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint32_t color)
{
    int32_t i, dx, dy, sdx, sdy, dxabs, dyabs, x, y;
    uint16_t px, py;

    dx    = x2 - x1; /* the horizontal distance of the line */
    dy    = y2 - y1; /* the vertical distance of the line */
    dxabs = abs (dx);
    dyabs = abs (dy);
    // sdx=(dx);
    if (dx < 0) sdx = -1;
    else
    {
        if (dx > 0) sdx = 1;
        else sdx = 0;
    }
    // sdy=sgn(dy);
    if (dy < 0) sdy = -1;
    else
    {
        if (dy > 0) sdy = 1;
        else sdy = 0;
    }
    x  = dyabs >> 1;
    y  = dxabs >> 1;
    px = x1;
    py = y1;

    if (dxabs >= dyabs) /* the line is more horizontal than vertical */
    {
        for (i = 0; i < dxabs; i++)
        {
            y += dyabs;
            if (y >= dxabs)
            {
                y -= dxabs;
                py += sdy;
            }
            px += sdx;
            SetPixel (px, py, color);
        }
    }
    else /* the line is more vertical than horizontal */
    {
        for (i = 0; i < dyabs; i++)
        {
            x += dxabs;
            if (x >= dyabs)
            {
                x -= dyabs;
                px += sdx;
            }
            py += sdy;
            SetPixel (px, py, color);
        }
    }
}

// fn: Draw Line with line_thickness and style
//
void Draw_line (
    uint32_t color,
    int32_t x0, int32_t y0,
    int32_t x1, int32_t y1,
    uint32_t line_thickness,
    uint32_t line_stile)
{
    int32_t delta_x, delta_y;
    int32_t error, step_error_lt, step_error_ge;
    int32_t step_x, step_y;
    int32_t step;
    int32_t style;
    int32_t type;
    int32_t i;
    // check for vertical or horisontal line
    if (x0 == x1)        // vertical line
    {
        if (y0 > y1) swap (y0, y1);

        style = 0;
        type  = 1;

        for (i = y0; i <= y1; i++)
        {
            if (++style == line_stile)
            {
                type ^= 1;
                style = 0;
            }

            if (type > 0)
            {
                SetPixel (x0, i, color);
                if (line_thickness > 0)
                {
                    SetPixel (x0 + 1, i, color);
                    SetPixel (x0 - 1, i, color);
                }
            }
        }

        return;
    }

    if (y0 == y1)        // horisontal line
    {
        if (x0 > x1) swap (x0, x1);

        style = 0;
        type  = 1;
        for (i = x0; i <= x1; i++)
        {
            if (++style == line_stile)
            {
                type ^= 1;
                style = 0;
            }

            if (type > 0)
            {
                SetPixel (i, y0, color);
                if (line_thickness > 0)
                {
                    SetPixel (i, y0 + 1, color);
                    SetPixel (i, y0 - 1, color);
                }
            }
        }

        return;
    }

    if ((delta_x = x1 - x0) < 0)
    {
        delta_x = abs (delta_x);
        step_x  = -1;
    }
    else step_x = 1;

    if ((delta_y = y1 - y0) < 0)
    {
        delta_y = abs (delta_y);
        step_y  = -1;
    }
    else step_y = 1;

    if (delta_x < delta_y)
    {
        step = 1;
        swap (delta_x, delta_y);
        swap (x0, y0);
        swap (step_x, step_y);
        SetPixel (x0, y0, color);
    }
    else
    {
        SetPixel (x0, y0, color);
        step = 0;
    }

    // If the current error greater or equal zero
    step_error_ge = delta_x * 2;

    // If the current error less than zero
    step_error_lt = delta_y * 2;

    // Error for the first pixel
    error = step_error_lt - delta_x;

    type  = 1;
    style = 0;
    while (--delta_x >= 0)
    {
        if (error >= 0)
        {
            y0 += step_y;
            error -= step_error_ge;
        }

        x0 += step_x;
        error += step_error_lt;

        if (++style == line_stile)
        {
            type ^= 1;
            style = 0;
        }

        if (type > 0)
        {
            if (step > 0)
            {
                SetPixel (x0, y0, color);
                if (line_thickness > 0)
                {
                    SetPixel (x0, y0 + 1, color);
                    SetPixel (x0, y0 - 1, color);
                }
            }
            else
            {
                SetPixel (x0, y0, color);
                if (line_thickness > 0)
                {
                    SetPixel (x0, y0 + 1, color);
                    SetPixel (x0, y0 + 1, color);
                }
            }
        }
    }
}

//============================================================
//
void drawRoundRect (int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color)
{
    // smarter version
    drawFastHLine (x + r, y, w - 2 * r, color);                // Top
    drawFastHLine (x + r, y + h - 1, w - 2 * r, color);        // Bottom
    drawFastVLine (x, y + r, h - 2 * r, color);                // Left
    drawFastVLine (x + w - 1, y + r, h - 2 * r, color);        // Right
    // draw four corners
    drawCircleHelper (x + r, y + r, r, 1, color);
    drawCircleHelper (x + w - r - 1, y + r, r, 2, color);
    drawCircleHelper (x + w - r - 1, y + h - r - 1, r, 4, color);
    drawCircleHelper (x + r, y + h - r - 1, r, 8, color);
}

//============================================================
//
// Draw a triangle
void drawTriangle (int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color)
{
    line_fast (x0, y0, x1, y1, color);
    line_fast (x1, y1, x2, y2, color);
    line_fast (x2, y2, x0, y0, color);
    //  drawLine(x0, y0, x1, y1, color);
    //  drawLine(x1, y1, x2, y2, color);
    //  drawLine(x2, y2, x0, y0, color);
}

// Fill a triangle
void fillTriangle (int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color)
{
    int16_t a, b, y, last;

    // Sort coordinates by Y order (y2 >= y1 >= y0)
    if (y0 > y1)
    {
        swap (y0, y1);
        swap (x0, x1);
    }
    if (y1 > y2)
    {
        swap (y2, y1);
        swap (x2, x1);
    }
    if (y0 > y1)
    {
        swap (y0, y1);
        swap (x0, x1);
    }

    if (y0 == y2)        // Handle awkward all-on-same-line case as its own thing
    {
        a = b = x0;
        if (x1 < a) a = x1;
        else if (x1 > b) b = x1;
        if (x2 < a) a = x2;
        else if (x2 > b) b = x2;
        drawFastHLine (a, y0, b - a + 1, color);
        return;
    }

    int16_t
        dx01 = x1 - x0,
        dy01 = y1 - y0,
        dx02 = x2 - x0,
        dy02 = y2 - y0,
        dx12 = x2 - x1,
        dy12 = y2 - y1,
        sa   = 0,
        sb   = 0;

    // For upper part of triangle, find scanline crossings for segments
    // 0-1 and 0-2.  If y1=y2 (flat-bottomed triangle), the scanline y1
    // is included here (and second loop will be skipped, avoiding a /0
    // error there), otherwise scanline y1 is skipped here and handled
    // in the second loop...which also avoids a /0 error here if y0=y1
    // (flat-topped triangle).
    if (y1 == y2) last = y1;        // Include y1 scanline
    else last = y1 - 1;             // Skip it

    for (y = y0; y <= last; y++)
    {
        a = x0 + sa / dy01;
        b = x0 + sb / dy02;
        sa += dx01;
        sb += dx02;
        /* longhand:
        a = x0 + (x1 - x0) * (y - y0) / (y1 - y0);
        b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
        */
        if (a > b) swap (a, b);
        drawFastHLine (a, y, b - a + 1, color);
    }

    // For lower part of triangle, find scanline crossings for segments
    // 0-2 and 1-2.  This loop is skipped if y1=y2.
    sa = dx12 * (y - y1);
    sb = dx02 * (y - y0);
    for (; y <= y2; y++)
    {
        a = x1 + sa / dy12;
        b = x0 + sb / dy02;
        sa += dx12;
        sb += dx02;
        /* longhand:
        a = x1 + (x2 - x1) * (y - y1) / (y2 - y1);
        b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
        */
        if (a > b) swap (a, b);
        drawFastHLine (a, y, b - a + 1, color);
    }
}

//============================================================
// show gray
void DispRGBGray (void)
{
    // unsigned int COL=320;
    unsigned char i, j, k, dbl, dbh;
    uint16_t dat;
    LCD_SetWindow_Write (0, LCD_WIDTH, 0, LCD_HEIGHT);
    // balck -> red
    for (k = 0; k < 80; k++)
    {
        for (i = 0; i < 32; i++)
        {
            for (j = 0; j < 10; j++)
            {
                dat = i << 11;
                Write_Data_U16 (dat);
            }
        }
    }
    // red -> black
    for (k = 0; k < 80; k++)
    {
        for (i = 31; i > 0; i--)
        {
            for (j = 0; j < 10; j++)
            {
                dat = i << 11;
                Write_Data_U16 (dat);
            }
        }
        dbh = 0x00;
        dbl = 0x00;
        for (i = 0; i < 10; i++)
            // Write_Data(dbh,dbl);
            Write_Data_U16 (0);
    }
    // balck -> green
    for (k = 0; k < 80; k++)
    {
        for (i = 0; i < 64; i += 2)
        {
            for (j = 0; j < 10; j++)
            {
                dbh = i >> 3;
                dat = dbh << 8;
                dbl = i << 5;
                dat |= dbl;
                Write_Data_U16 (dat);
            }
        }
    }
    // green -> black
    for (k = 0; k < 80; k++)
    {
        for (i = 63; i != 1; i -= 2)
        {
            for (j = 0; j < 10; j++)
            {
                dbh = i >> 3;
                dat = dbh << 8;
                dbl = i << 5;
                dat |= dbl;
                Write_Data_U16 (dat);
            }
        }
        dbh = 0x00;
        dbl = 0x00;
        for (i = 0; i < 10; i++)
            // Write_Data(dbh,dbl);
            Write_Data_U16 (0);
    }
    // balck -> blue
    for (k = 0; k < 80; k++)
    {
        for (i = 0; i < 32; i++)
        {
            for (j = 0; j < 10; j++)
            {
                dbh = 0;
                dbl = i;
                // Write_Data(dbh,dbl);
                Write_Data_U16 (i);
            }
        }
    }
    // blue -> black
    for (k = 0; k < 80; k++)
    {
        for (i = 31; i > 0; i--)
        {
            for (j = 0; j < 10; j++)
            {
                dbh = 0;
                dbl = i;
                Write_Data_U16 (i);
            }
        }
        dbh = 0x00;
        dbl = 0x00;
        for (i = 0; i < 10; i++)
            // Write_Data(dbh,dbl);
            Write_Data_U16 (0);
    }
}

void lcd_hline (uint16_t x1, uint16_t x2, uint16_t y, uint32_t color)
{
    if (x1 >= x2) SWAP (x1, x2);
    for (; x1 <= x2; x1++) SetPixel (x1, y, color);
}

// Fill a triangle - Bresenham method
// Original from http://www.sunshine2k.de/coding/java/TriangleRasterization/TriangleRasterization.html
void fillTriangle1 (uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint32_t c)
{
    uint16_t t1x, t2x, y, minx, maxx, t1xp, t2xp;
    bool changed1 = false;
    bool changed2 = false;
    int16_t signx1, signx2, dx1, dy1, dx2, dy2;
    uint16_t e1, e2;
    // Sort vertices
    if (y1 > y2)
    {
        SWAP (y1, y2);
        SWAP (x1, x2);
    }
    if (y1 > y3)
    {
        SWAP (y1, y3);
        SWAP (x1, x3);
    }
    if (y2 > y3)
    {
        SWAP (y2, y3);
        SWAP (x2, x3);
    }

    t1x = t2x = x1;
    y         = y1;        // Starting points

    dx1 = (int8_t) (x2 - x1);
    if (dx1 < 0)
    {
        dx1    = -dx1;
        signx1 = -1;
    }
    else signx1 = 1;
    dy1 = (int8_t) (y2 - y1);

    dx2 = (int8_t) (x3 - x1);
    if (dx2 < 0)
    {
        dx2    = -dx2;
        signx2 = -1;
    }
    else signx2 = 1;
    dy2 = (int8_t) (y3 - y1);

    if (dy1 > dx1)
    {        // swap values
        SWAP (dx1, dy1);
        changed1 = true;
    }
    if (dy2 > dx2)
    {        // swap values
        SWAP (dy2, dx2);
        changed2 = true;
    }

    e2 = (uint8_t) (dx2 >> 1);
    // Flat top, just process the second half
    if (y1 == y2) goto next;
    e1 = (uint16_t) (dx1 >> 1);

    for (uint16_t i = 0; i < dx1;)
    {
        t1xp = 0;
        t2xp = 0;
        if (t1x < t2x)
        {
            minx = t1x;
            maxx = t2x;
        }
        else
        {
            minx = t2x;
            maxx = t1x;
        }
        // process first line until y value is about to change
        while (i < dx1)
        {
            i++;
            e1 += dy1;
            while (e1 >= dx1)
            {
                e1 -= dx1;
                if (changed1) t1xp = signx1;        // t1x += signx1;
                else goto next1;
            }
            if (changed1) break;
            else t1x += signx1;
        }
    // Move line
    next1:
        // process second line until y value is about to change
        while (1)
        {
            e2 += dy2;
            while (e2 >= dx2)
            {
                e2 -= dx2;
                if (changed2) t2xp = signx2;        // t2x += signx2;
                else goto next2;
            }
            if (changed2) break;
            else t2x += signx2;
        }
    next2:
        if (minx > t1x) minx = t1x;
        if (minx > t2x) minx = t2x;
        if (maxx < t1x) maxx = t1x;
        if (maxx < t2x) maxx = t2x;
        lcd_hline (minx, maxx, y, c);        // Draw line from min to max points found on the y
        // Now increase y
        if (!changed1) t1x += signx1;
        t1x += t1xp;
        if (!changed2) t2x += signx2;
        t2x += t2xp;
        y += 1;
        if (y == y2) break;
    }
next:
    // Second half
    dx1 = (int8_t) (x3 - x2);
    if (dx1 < 0)
    {
        dx1    = -dx1;
        signx1 = -1;
    }
    else signx1 = 1;
    dy1 = (int8_t) (y3 - y2);
    t1x = x2;

    if (dy1 > dx1)
    {        // swap values
        SWAP (dy1, dx1);
        changed1 = true;
    }
    else changed1 = false;

    e1 = (uint16_t) (dx1 >> 1);

    for (uint16_t i = 0; i <= dx1; i++)
    {
        t1xp = 0;
        t2xp = 0;
        if (t1x < t2x)
        {
            minx = t1x;
            maxx = t2x;
        }
        else
        {
            minx = t2x;
            maxx = t1x;
        }
        // process first line until y value is about to change
        while (i < dx1)
        {
            e1 += dy1;
            while (e1 >= dx1)
            {
                e1 -= dx1;
                if (changed1)
                {
                    t1xp = signx1;
                    break;
                }        // t1x += signx1;
                else goto next3;
            }
            if (changed1) break;
            else t1x += signx1;
            if (i < dx1) i++;
        }
    next3:
        // process second line until y value is about to change
        while (t2x != x3)
        {
            e2 += dy2;
            while (e2 >= dx2)
            {
                e2 -= dx2;
                if (changed2) t2xp = signx2;
                else goto next4;
            }
            if (changed2) break;
            else t2x += signx2;
        }
    next4:

        if (minx > t1x) minx = t1x;
        if (minx > t2x) minx = t2x;
        if (maxx < t1x) maxx = t1x;
        if (maxx < t2x) maxx = t2x;
        lcd_hline (minx, maxx, y, c);        // Draw line from min to max points found on the y
        // Now increase y
        if (!changed1) t1x += signx1;
        t1x += t1xp;
        if (!changed2) t2x += signx2;
        t2x += t2xp;
        y += 1;
        if (y > y3) return;
    }
}

//================ B U F E R ===================================================
//==============================================================================
uint16_t WIDTH, HEIGHT;
uint16_t Buffer [14400];

// void WritePicFlash(unsigned char xstart,unsigned char ystart, unsigned char xlong, unsigned char ylong,uint32_t start_addr)
//{
//   uint8_t *pic;
//   uint32_t temp;
//   temp=xlong*ylong;
//  //pic = (char *) malloc(xlong*ylong);
//   if(uxTaskGetNumberOfTasks())
//         pic=pvPortMalloc(temp);
//     else
//         pic=malloc(temp);
//
//   SSTxReadMultiByte(&hspi2, 1, start_addr, pic,temp );
//   //osDelay(1);
//   write_pic(xstart,ystart,xlong,ylong,pic);
//   //osDelay(1);
//   if(uxTaskGetNumberOfTasks())
//         vPortFree( pic );
//     else
//         free( pic );
// }

void MallocBuff (uint16_t * Buff, uint16_t w, uint16_t h)
{
    // if(uxTaskGetNumberOfTasks())
    Buff = pvPortMalloc (w * h);
    // else
    //     buff=malloc(w*h);
}

void FreeBuff (uint16_t * Buff)
{
    // if(uxTaskGetNumberOfTasks())
    if (Buff) vPortFree (Buff);
    // else
    //     free( buff );
}

void DefineBuff (uint16_t w, uint16_t h)
{
    WIDTH  = w;
    HEIGHT = h;
}

void SetPixelBuff (uint16_t * Buff, uint16_t x, uint16_t y, uint16_t color)
{
    uint16_t temp;
    temp            = y * WIDTH;
    Buff [x + temp] = color;
}

void Draw_Circle_Buff (uint16_t * Buff, int16_t x0, int16_t y0, int16_t r, uint16_t color)
{
    int16_t f     = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x     = 0;
    int16_t y     = r;

    SetPixelBuff (Buff, x0, y0 + r, color);
    SetPixelBuff (Buff, x0, y0 - r, color);
    SetPixelBuff (Buff, x0 + r, y0, color);
    SetPixelBuff (Buff, x0 - r, y0, color);

    while (x < y)
    {
        if (f >= 0)
        {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        SetPixelBuff (Buff, x0 + x, y0 + y, color);
        SetPixelBuff (Buff, x0 - x, y0 + y, color);
        SetPixelBuff (Buff, x0 + x, y0 - y, color);
        SetPixelBuff (Buff, x0 - x, y0 - y, color);
        SetPixelBuff (Buff, x0 + y, y0 + x, color);
        SetPixelBuff (Buff, x0 - y, y0 + x, color);
        SetPixelBuff (Buff, x0 + y, y0 - x, color);
        SetPixelBuff (Buff, x0 - y, y0 - x, color);
    }
    // DrawObject((uint16_t *)Buff , SetWindow (340,0,120-1,120-1));
}

void Draw_Line_Buff (uint16_t * Buff, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint32_t color)
{
    int32_t i, dx, dy, sdx, sdy, dxabs, dyabs, x, y;
    uint16_t px, py;

    dx    = x2 - x1; /* the horizontal distance of the line */
    dy    = y2 - y1; /* the vertical distance of the line */
    dxabs = abs (dx);
    dyabs = abs (dy);
    // sdx=(dx);
    if (dx < 0) sdx = -1;
    else
    {
        if (dx > 0) sdx = 1;
        else sdx = 0;
    }
    // sdy=sgn(dy);
    if (dy < 0) sdy = -1;
    else
    {
        if (dy > 0) sdy = 1;
        else sdy = 0;
    }
    x  = dyabs >> 1;
    y  = dxabs >> 1;
    px = x1;
    py = y1;

    if (dxabs >= dyabs) /* the line is more horizontal than vertical */
    {
        for (i = 0; i < dxabs; i++)
        {
            y += dyabs;
            if (y >= dxabs)
            {
                y -= dxabs;
                py += sdy;
            }
            px += sdx;
            SetPixelBuff (Buff, px, py, color);
        }
    }
    else /* the line is more vertical than horizontal */
    {
        for (i = 0; i < dyabs; i++)
        {
            x += dxabs;
            if (x >= dyabs)
            {
                x -= dyabs;
                px += sdx;
            }
            py += sdy;
            SetPixelBuff (Buff, px, py, color);
        }
    }
}

void lcd_hline_Buff (uint16_t * Buff, uint16_t x1, uint16_t x2, uint16_t y, uint32_t color)
{
    if (x1 >= x2) SWAP (x1, x2);
    for (; x1 <= x2; x1++) SetPixelBuff (Buff, x1, y, color);
}

void Fill_Triangle_Buff (uint16_t * Buff, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint32_t c)
{
    uint16_t t1x, t2x, y, minx, maxx, t1xp, t2xp;
    bool changed1 = false;
    bool changed2 = false;
    int16_t signx1, signx2, dx1, dy1, dx2, dy2;
    uint16_t e1, e2;
    // Sort vertices
    if (y1 > y2)
    {
        SWAP (y1, y2);
        SWAP (x1, x2);
    }
    if (y1 > y3)
    {
        SWAP (y1, y3);
        SWAP (x1, x3);
    }
    if (y2 > y3)
    {
        SWAP (y2, y3);
        SWAP (x2, x3);
    }

    t1x = t2x = x1;
    y         = y1;        // Starting points

    dx1 = (int8_t) (x2 - x1);
    if (dx1 < 0)
    {
        dx1    = -dx1;
        signx1 = -1;
    }
    else signx1 = 1;
    dy1 = (int8_t) (y2 - y1);

    dx2 = (int8_t) (x3 - x1);
    if (dx2 < 0)
    {
        dx2    = -dx2;
        signx2 = -1;
    }
    else signx2 = 1;
    dy2 = (int8_t) (y3 - y1);

    if (dy1 > dx1)
    {
        SWAP (dx1, dy1);        // swap values
        changed1 = true;
    }
    if (dy2 > dx2)
    {
        SWAP (dy2, dx2);        // swap values
        changed2 = true;
    }

    e2 = (uint8_t) (dx2 >> 1);
    // Flat top, just process the second half
    if (y1 == y2) goto next;
    e1 = (uint16_t) (dx1 >> 1);

    for (uint16_t i = 0; i < dx1;)
    {
        t1xp = 0;
        t2xp = 0;
        if (t1x < t2x)
        {
            minx = t1x;
            maxx = t2x;
        }
        else
        {
            minx = t2x;
            maxx = t1x;
        }
        // process first line until y value is about to change
        while (i < dx1)
        {
            i++;
            e1 += dy1;
            while (e1 >= dx1)
            {
                e1 -= dx1;
                if (changed1) t1xp = signx1;        // t1x += signx1;
                else goto next1;
            }
            if (changed1) break;
            else t1x += signx1;
        }
    // Move line
    next1:
        // process second line until y value is about to change
        while (1)
        {
            e2 += dy2;
            while (e2 >= dx2)
            {
                e2 -= dx2;
                if (changed2) t2xp = signx2;        // t2x += signx2;
                else goto next2;
            }
            if (changed2) break;
            else t2x += signx2;
        }
    next2:
        if (minx > t1x) minx = t1x;
        if (minx > t2x) minx = t2x;
        if (maxx < t1x) maxx = t1x;
        if (maxx < t2x) maxx = t2x;
        // lcd_hline(minx, maxx, y,c);    // Draw line from min to max points found on the y
        lcd_hline_Buff (Buff, minx, maxx, y, c);
        // Now increase y
        if (!changed1) t1x += signx1;
        t1x += t1xp;
        if (!changed2) t2x += signx2;
        t2x += t2xp;
        y += 1;
        if (y == y2) break;
    }
next:
    // Second half
    dx1 = (int8_t) (x3 - x2);
    if (dx1 < 0)
    {
        dx1    = -dx1;
        signx1 = -1;
    }
    else signx1 = 1;
    dy1 = (int8_t) (y3 - y2);
    t1x = x2;

    if (dy1 > dx1)
    {        // swap values
        SWAP (dy1, dx1);
        changed1 = true;
    }
    else changed1 = false;

    e1 = (uint16_t) (dx1 >> 1);

    for (uint16_t i = 0; i <= dx1; i++)
    {
        t1xp = 0;
        t2xp = 0;
        if (t1x < t2x)
        {
            minx = t1x;
            maxx = t2x;
        }
        else
        {
            minx = t2x;
            maxx = t1x;
        }
        // process first line until y value is about to change
        while (i < dx1)
        {
            e1 += dy1;
            while (e1 >= dx1)
            {
                e1 -= dx1;
                if (changed1)
                {
                    t1xp = signx1;
                    break;
                }        // t1x += signx1;
                else goto next3;
            }
            if (changed1) break;
            else t1x += signx1;
            if (i < dx1) i++;
        }
    next3:
        // process second line until y value is about to change
        while (t2x != x3)
        {
            e2 += dy2;
            while (e2 >= dx2)
            {
                e2 -= dx2;
                if (changed2) t2xp = signx2;
                else goto next4;
            }
            if (changed2) break;
            else t2x += signx2;
        }
    next4:

        if (minx > t1x) minx = t1x;
        if (minx > t2x) minx = t2x;
        if (maxx < t1x) maxx = t1x;
        if (maxx < t2x) maxx = t2x;
        lcd_hline_Buff (Buff, minx, maxx, y, c);        // Draw line from min to max points found on the y
        // Now increase y
        if (!changed1) t1x += signx1;
        t1x += t1xp;
        if (!changed2) t2x += signx2;
        t2x += t2xp;
        y += 1;
        if (y > y3) return;
    }
}
