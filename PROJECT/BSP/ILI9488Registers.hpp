/// \brief ILI9488Registers class
/// \file
/// \version 1 \date 26.06.2024

namespace BSP
{
    /// \brief ILI9488 registers
    /// \see https://www.hpinfotech.ro/ILI9488.pdf#page=139&zoom=auto,-273,141
    class ILI9488Registers
    {
    public:

        enum
        {
            NOP               = 0,           ///< https://www.hpinfotech.ro/ILI9488.pdf#page=148&zoom=auto,-273,157
            SOFT_RESET        = 0x01,        ///<  https://www.hpinfotech.ro/ILI9488.pdf#page=149&zoom=auto,-273,45
            READ_DISPLAY_INFO = 0x04,        ///< [Read Display Identification Information (04h)](https://www.hpinfotech.ro/ILI9488.pdf#page=151)
        };
    };
}        // namespace BSP
