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
    float angle (processValue (value));
    textureMapperAngleCompass.setAngles (0, 0, angle);
    textureMapperAngleCompass.invalidate ();
}

void screenView::buttonClickEvent ()
{
    presenter->setValue (123);
}

float screenView::processValue (uint32_t value) const
{
}
