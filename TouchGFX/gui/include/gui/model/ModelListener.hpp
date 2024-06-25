#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include <gui/model/Model.hpp>

class ModelListener
{
public:

    ModelListener () : model (0) {}

    virtual ~ModelListener () {}

    void bind (Model * m)
    {
        model = m;
    }

    // --------------------------- User Events ----------------------------

    /// \brief Compass angle changed event
    /// \param value
    virtual void onCompassAngleChanged (uint32_t value) {}

protected:

    Model * model;
};

#endif        // MODELLISTENER_HPP
