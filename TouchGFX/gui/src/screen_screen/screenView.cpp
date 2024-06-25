#include <gui/screen_screen/screenView.hpp>

screenView::screenView ()
{
}

void screenView::setupScreen ()
{
    screenViewBase::setupScreen ();
}

void screenView::tearDownScreen ()
{
    screenViewBase::tearDownScreen ();
}

void screenView::updateCompassNeedle (uint32_t value)
{
    // TODO: convert `value` to float ...

    float angle;
    textureMapperAngleCompass.setAngles (0, 0, angle);
    textureMapperAngleCompass.invalidate ();
}
