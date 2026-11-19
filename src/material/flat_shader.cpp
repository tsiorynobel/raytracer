#include "material/flat_shader.h"

FlatShader::FlatShader(const Colour& colour) : _colour(colour) {}

Colour FlatShader::shade(const Ray& /* ray */) const {
    return _colour;
}
