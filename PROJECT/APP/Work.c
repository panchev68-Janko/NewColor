/* Includes ------------------------------------------------------------------*/

#include "app_touchgfx.h"
#include "cmsis_os.h"
#include "crc.h"
#include "dma.h"
#include "fsmc.h"
#include "gpio.h"
#include "i2c.h"
#include "main.h"
#include "rtc.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"

static uint32_t angleCompass, varRead;

uint32_t getAngleCompass (void)
{
    return angleCompass;
}

void returnFromTouchGFX (uint32_t var)
{
    varRead = var;
}

void StartDefaultTask (void const * argument)
{
    while (1)
    {
        angleCompass++;
        osDelay (50);
    }
}
