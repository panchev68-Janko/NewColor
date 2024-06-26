/// \brief BSP instances
/// \file
/// \version 1 \date 26.06.2024

#pragma once
#include "BSP/ILI9488.hpp"

extern DMA_HandleTypeDef hdma_memtomem_dma2_stream0;
constexpr uint32_t TFT_REG_ADDR  = 0x6C000000;
constexpr uint32_t TFT_DATA_ADDR = 0x6C000080;

namespace BSP
{
    inline ILI9488 tft ({&hdma_memtomem_dma2_stream0, TFT_REG_ADDR, TFT_DATA_ADDR});
}
