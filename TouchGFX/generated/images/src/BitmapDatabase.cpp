// 4.24.0 0x98f460c5
// Generated by imageconverter. Please, do not edit!

#include <images/BitmapDatabase.hpp>
#include <touchgfx/Bitmap.hpp>

extern const unsigned char image_compassneedle[]; // BITMAP_COMPASSNEEDLE_ID = 0, Size: 30x180 pixels

const touchgfx::Bitmap::BitmapData bitmap_database[] = {
    { image_compassneedle, 0, 30, 180, 7, 75, 16, ((uint8_t)touchgfx::Bitmap::ARGB8888) >> 3, 29, ((uint8_t)touchgfx::Bitmap::ARGB8888) & 0x7 }
};

namespace BitmapDatabase
{
const touchgfx::Bitmap::BitmapData* getInstance()
{
    return bitmap_database;
}

uint16_t getInstanceSize()
{
    return (uint16_t)(sizeof(bitmap_database) / sizeof(touchgfx::Bitmap::BitmapData));
}
} // namespace BitmapDatabase
