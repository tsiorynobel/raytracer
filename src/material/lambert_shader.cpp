#include "material/lambert_shader.h"
#include <algorithm>

LambertShader::LambertShader(const Colour& colour) : _colour(colour) {}

Colour LambertShader::shade(const Vector& normal, const Vector& toLight) const {
    // Facing away from the light gives a negative cosine: no light, not less than none.
    double brightness = std::max(0.0, normal.dot(toLight));
    return brightness * _colour;
}
