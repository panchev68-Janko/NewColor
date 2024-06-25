#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

extern "C" uint32_t getAngleCompass ();
extern "C" void setFromTouchGFX (uint32_t value);

static uint32_t angleCompass = -1UL;
static uint32_t varRead;

Model::Model () : modelListener (0)
{
}

void Model::tick ()
{
    // handle the angleCompass value
    if (getAngleCompass () != angleCompass)
    {
        angleCompass = getAngleCompass ();
        modelListener->onCompassAngleChanged (angleCompass);
    }
    // ...
}
