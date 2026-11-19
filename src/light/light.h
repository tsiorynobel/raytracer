#pragma once

#include "math/vector.h"
#include "colour/colour.h"

// A point light: where the light comes from, and the colour it gives.
class Light {
private:
    Vector _position;
    Colour _colour;

public:
    Light(const Vector& position, const Colour& colour);

    const Vector& position() const;
    const Colour& colour() const;
};
