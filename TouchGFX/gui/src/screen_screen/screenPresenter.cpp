#include <gui/screen_screen/screenPresenter.hpp>
#include <gui/screen_screen/screenView.hpp>

screenPresenter::screenPresenter (screenView & v)
                                : view (v)
{
}

void screenPresenter::activate ()
{
}

void screenPresenter::deactivate ()
{
}

void screenPresenter::onCompassAngleChanged (uint32_t value)
{
    view.updateCompassNeedle (value);
}
