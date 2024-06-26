/// \brief DisplayInterface class
/// \file

#pragma once

#include "Middlewares/Third_Party/FreeRTOS/Source/include/projdefs.h"
#include "Middlewares/Third_Party/FreeRTOS/Source/include/semphr.h"
#include "assert.h"
#include "stm32f4xx_hal_dma.h"

namespace BSP
{
    /// \brief DisplayInterface class
    class DisplayInterface
    {
    protected:

        struct Config
        {
            DMA_HandleTypeDef * dmaHandle;        // hdma_memtomem_dma2_stream0
            uint32_t regAddress;                  // 0x6C000000
            uint32_t dataAddress;                 // 0x6C000080
        };

        /// \brief DisplayInterface constructor
        DisplayInterface (const Config & config)
        {
            assert (_instance && "The object has already been created");
            _instance = this;
            assert (_dmaHandle);
            _dmaHandle   = config.dmaHandle;
            _regAddress  = config.regAddress;
            _dataAddress = config.dataAddress;
        }

        /// \brief DisplayInterface destructor
        virtual ~DisplayInterface () = default;

        /// \brief Initialize the display interface
        virtual void init ()
        {
            auto callback = [] (__DMA_HandleTypeDef * hdma) { _instance->completeCallback (hdma); };
            auto result   = HAL_DMA_RegisterCallback (_dmaHandle, HAL_DMA_CallbackIDTypeDef::HAL_DMA_XFER_CPLT_CB_ID, callback) == HAL_OK;
            assert (result);

            // create the semaphore
            _semaphoreHandle = xSemaphoreCreateBinary ();
            assert (_semaphoreHandle != nullptr);
        }

        /// \brief De-initialize the display interface
        virtual void deinit ()
        {
            auto result = HAL_DMA_UnRegisterCallback (_dmaHandle, HAL_DMA_CallbackIDTypeDef::HAL_DMA_XFER_CPLT_CB_ID) == HAL_OK;
            assert (result);
        }

        /// \brief Write TFT register
        /// \param value
        void writeReg (uint16_t value)
        {
            *(volatile uint16_t *) _regAddress = value;
        }

        /// \brief Write TFT data
        /// \param value
        void writeData (uint16_t value)
        {
            *(volatile uint16_t *) _dataAddress = value;
        }

        /// \brief Write TFT data block
        /// \param data
        /// \param len
        void writeData (const uint8_t * data, size_t len)
        {
            for (auto i = 0; i < len; i++) writeData (data [i]);
        }

        /// \brief Write block
        /// \param src
        /// \param size
        /// \return bool
        bool writeblock (const void * src, size_t size)
        {
            assert (size <= 0xffff);
            assert (src);
            auto block = reinterpret_cast<const uint32_t> (src);
            if (HAL_DMA_Start_IT (_dmaHandle, block, _dataAddress, size) != HAL_OK)
            {
                assert (0);
                return false;
            }
            return true;
        }

        virtual bool waitForCompleted (uint32_t timeout)
        {
            return (xSemaphoreTake (_semaphoreHandle, timeout) == pdTRUE);
        }

    private:

        void completeCallback (__DMA_HandleTypeDef * hdma)
        {
            auto result = xSemaphoreGive (_semaphoreHandle);
            assert (result == pdTRUE);
        }

        DMA_HandleTypeDef * _dmaHandle;
        uint32_t _regAddress;
        uint32_t _dataAddress;
        static inline DisplayInterface * _instance = nullptr;
        SemaphoreHandle_t _semaphoreHandle;
    };
}        // namespace BSP
