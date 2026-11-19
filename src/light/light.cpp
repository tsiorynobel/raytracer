#include "light/light.h"

Light::Light(const Vector& position, const Colour& colour)
    : _position(position), _colour(colour) {}

const Vector& Light::position() const { return _position; }

const Colour& Light::colour() const { return _colour; }
