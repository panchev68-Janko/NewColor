/// \brief ILI9488 class
/// \details TFT Display Driver
/// \file
/// \version 1 \date 26.06.2024

#pragma once

/// \brief Get high byte from word
/// \param  x - word
/// \return byte
#define HI_BYTE(x) (uint8_t) (x >> 8)

///  \brief Get low byte from word
/// \param  x - word
/// \return byte
#define LO_BYTE(x) (uint8_t) (x & 0x00ff)

#include "DisplayInterface.hpp"
#include "ILI9488Registers.hpp"
#include "Middlewares/Third_Party/FreeRTOS/Source/include/task.h"

namespace BSP
{
    /// \brief TFT LCD Single Chip Driver
    /// \details  TFT LCD Single Chip Driver 320(RGB) x 480 Resolution, 16.7M-color With Internal GRAM
    /// \details https://www.hpinfotech.ro/ILI9488.pdf
    class ILI9488 : DisplayInterface
    {
    public:

        using Config = DisplayInterface::Config;

        /// \brief ILI9488 constructor
        /// \param config - reference to config
        ILI9488 (const Config & config) : DisplayInterface (config)
        {}

        /// \brief ILI9488 destructor
        ~ILI9488 () = default;

        /// \brief Initalize the ILI9488
        void init () override
        {
            __packed uint8_t initData [] =
                {
                    16, 0xE0, 0x00, 0x03, 0x09, 0x08, 0x16, 0x0A, 0x3F, 0x78, 0x4C, 0x09, 0x0A, 0x08, 0x16, 0x1A, 0x0F,        // PGAMCTRL(Positive Gamma Control)
                    16, 0xE1, 0x00, 0x16, 0x19, 0x03, 0x0F, 0x05, 0x32, 0x45, 0x46, 0x04, 0x0E, 0x0D, 0x35, 0x37, 0x0F,        // NGAMCTRL(Negative Gamma Control)
                    3, 0xC0, 0x17, 0x15,                                                                                       // Power Control 1
                    2, 0xC1, 0x41,                                                                                             // Power Control 2
                    4, 0xC5, 0x00, 0x12, 0x80,                                                                                 // Power Control 3
                    2, 0x36, 0x48,                                                                                             // Memory Access
                    2, 0x3a, 0x55,                                                                                             // Interface Pixel Format = 16bits
                    2, 0xb0, 0x00,                                                                                             // Interface Mode Control
                    2, 0xb1, 0xa0,                                                                                             // Frame rate = 60Hz
                    2, 0xb4, 0x02,                                                                                             // Display Inversion Control = 2 dot
                    3, 0xb6, 0x02, 0x02,                                                                                       // Display Function Control  RGB/MCU Interface Control
                    2, 0xe9, 0x00,                                                                                             // Set Image Function = Disable 24 bit data
                    2, 0xf7, 0xa9, 0x51, 0x2c, 0x82,                                                                           // Adjust Control = D7 stream, loose
                    1, 0x11,                                                                                                   // Sleep out
                    0

                };

            __packed struct Command
            {
                uint8_t len;
                uint8_t cmd;
                uint8_t data;
            };

            const uint8_t * initSequence = initData;
            DisplayInterface::init ();

            // initialize the diaplay...

            for (;;)
            {
                auto * row = reinterpret_cast<const Command *> (initSequence);
                if (row->len == 0) break;
                writeReg (row->cmd);
                initSequence = &row->data;
                for (auto i = 0; i < row->len - 1; i++) writeData (initSequence [i]);
                initSequence += row->len - 1;
            }
            setMemoryAccessControl (0x28);
        }

        /// \brief De-initalize the ILI9488
        void deinit () override
        {
            DisplayInterface::deinit ();
        }

        /// \brief Set the Memory Access Control
        /// \param access
        /// \see [Memory Access Control (36h)](https://www.hpinfotech.ro/ILI9488.pdf#page=191&zoom=auto,-273,2)
        void setMemoryAccessControl (uint8_t access)
        {
            writeReg (0x36);        // Memory Access Control (36h) https://www.hpinfotech.ro/ILI9488.pdf#page=191&zoom=auto,-273,2)
            writeData (access);
            vTaskDelay (120);
        }

        /// \brief Transmit block to the display
        /// \param data     - pointer to buffer
        /// \param x        - X coordinate
        /// \param y        - Y coordinate
        /// \param width    - buffer width
        /// \param height   - height per buffer
        /// \return The length of the copied data in bytes
        void transmitBlock (const void * src, uint32_t x, uint32_t y, size_t width, size_t height)
        {
            auto size         = setWindow (x, y, width, height);
            _transmitIsActive = true;
            DisplayInterface::writeblock (src, size);
        }

        void transferCpltCallback ()
        {
            _transmitIsActive = false;
        }

    private:

        bool _transmitIsActive = false;

        size_t setWindow (uint32_t x, uint32_t y, uint32_t w, uint32_t h)
        {
            auto setPosReg = [this] (uint8_t reg, uint16_t start, uint16_t end) {
                DisplayInterface::writeReg (reg);
                uint8_t data [4] = {HI_BYTE (start), LO_BYTE (start), HI_BYTE (end), LO_BYTE (end)};
                DisplayInterface::writeData (data, sizeof (data));
            };

            setPosReg (0x2a, x, x + w - 1);           // Column Address Set (2Ah) https://www.hpinfotech.ro/ILI9488.pdf#page=174&zoom=auto,-273,110
            setPosReg (0x2b, y, y + h - 1);           // PASET (Page Address Set) https://www.hpinfotech.ro/ILI9488.pdf#page=177&zoom=auto,-273,800
            DisplayInterface::writeReg (0x2c);        // Memory Write (2Ch) https://www.hpinfotech.ro/ILI9488.pdf#page=179&zoom=auto,-273,778
            return (w * h);
        }
    };
}        // namespace BSP
