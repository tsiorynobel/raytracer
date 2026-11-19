#include "material/lambert_shader.h"
#include <algorithm>
#include "geometry/hit_info.h"
#include "light/light.h"

LambertShader::LambertShader(const Colour& colour) : _colour(colour) {}

Colour LambertShader::shade(const HitInfo& hit, const Light& light) const {
    Vector toLight = (light.position() - hit.point).normalised();
    // Facing away from the light gives a negative cosine: no light, not less than none.
    double intensity = std::max(0.0, hit.normal.dot(toLight));
    return _colour * light.colour() * intensity;
}
