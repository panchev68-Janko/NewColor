#ifndef _COMMON_H_
#define _COMMON_H_

#ifdef __cplusplus
extern "C" {
#endif


// C++ definitions
#ifdef __cplusplus
#define GetOwnerHandler(base_class_type, nested_instance) (reinterpret_cast<base_class_type*> (reinterpret_cast<char *>(this)- offsetof(base_class_type,nested_instance)))
#endif



#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <intrinsics.h>


    // F0 series
#if defined (STM32F030x6)

#include "stm32f0xx_hal.h"
#include "stm32f0xx.h"
#ifndef   __LIBRARY
#include "stm32f0xx_it.h"
#endif

    // F1 series
#elif defined (STM32F103xB) || defined (STM32F103xE)
#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#ifndef   __LIBRARY
#include "stm32f1xx_it.h"
#endif


    // F4 series
#elif defined (STM32F417xx)
#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"
#ifndef   __LIBRARY
#include "stm32f4xx_it.h"
#endif

#endif



#ifdef USE_FREERTOS
#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "task.h"
#endif

#define PIN(p) p##_GPIO_Port,p##_Pin
#ifdef __cplusplus
}
#endif
#endif