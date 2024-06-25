#ifndef SCREENPRESENTER_HPP
#define SCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class screenView;

class screenPresenter : public touchgfx::Presenter, public ModelListener
{
public:

    screenPresenter (screenView & v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate ();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate ();

    virtual ~screenPresenter () {}

private:

    screenPresenter ();

    screenView & view;

    // --------------------------- User Events ----------------------------

    /// \brief Compass angle changed event
    /// \param value
    /// \pre overridden from Model Listener
    void onCompassAngleChanged (uint32_t value) override;
};

#endif        // SCREENPRESENTER_HPP
