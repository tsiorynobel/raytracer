#include "colour/colour.h"

Colour::Colour(double r, double g, double b) : _r(r), _g(g), _b(b) {}

double Colour::r() const { return _r; }
double Colour::g() const { return _g; }
double Colour::b() const { return _b; }

Colour Colour::operator*(double t) const {
    return Colour(_r * t, _g * t, _b * t);
}

Colour Colour::operator*(const Colour& other) const {
    return Colour(_r * other._r, _g * other._g, _b * other._b);
}
