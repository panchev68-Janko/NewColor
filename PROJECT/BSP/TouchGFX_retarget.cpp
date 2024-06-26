#include "PROJECT/BSP.inl"

/// \brief Display Driver Transmit Active
/// \ingroup TouchGFX
extern "C" int touchgfxDisplayDriverTransmitActive ()
{
    return BSP::tft.getTransmitActive () ? 1 : 0;
}

/// \brief Display Driver Should Transfer Block callback
/// \param bottom
/// \return int
/// \ingroup TouchGFX
extern "C" int touchgfxDisplayDriverShouldTransferBlock (uint16_t bottom)
{
    return 1;
}

///  \brief Display Driver Transmit Block
/// \details Copy Buffer to Display
/// \param[in] src - pointer to source buffer
/// \param[in] x - X Position
/// \param[in] y - Y Position
/// \param[in] width - Width of Window
/// \param[in] height - Height of Window
/// \return size of transmitted block
/// \ingroup TouchGFX
extern "C" void touchgfxDisplayDriverTransmitBlock (const uint8_t * src, uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
    BSP::tft.transmitBlock (reinterpret_cast<const uint16_t *> (src), x, y, w, h);
}
