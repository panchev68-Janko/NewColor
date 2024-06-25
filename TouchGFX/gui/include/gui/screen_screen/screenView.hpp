#ifndef SCREENVIEW_HPP
#define SCREENVIEW_HPP

#include <gui/screen_screen/screenPresenter.hpp>
#include <gui_generated/screen_screen/screenViewBase.hpp>

class screenView : public screenViewBase
{
public:

    screenView ();

    virtual ~screenView () {}

    virtual void setupScreen ();
    virtual void tearDownScreen ();

    // ------------------------- User functions ---------------------------

    /// \brief Update compass needle
    /// \param value
    void updateCompassNeedle (uint32_t value);

protected:

private:

    uint32_t _positionX = 0;
};

#endif        // SCREENVIEW_HPP
