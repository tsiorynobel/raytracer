#include "material/flat_shader.h"

FlatShader::FlatShader(const Colour& colour) : _colour(colour) {}

Colour FlatShader::shade(const Vector& /* normal */, const Vector& /* toLight */) const {
    return _colour;
}
