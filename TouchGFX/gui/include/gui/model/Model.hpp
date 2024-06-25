#ifndef MODEL_HPP
#define MODEL_HPP

class ModelListener;

class Model
{
public:

    Model ();

    void bind (ModelListener * listener)
    {
        modelListener = listener;
    }

    void tick ();

    void setValue (uint32_t value);

protected:

    ModelListener * modelListener;
};

#endif        // MODEL_HPP
