#pragma once

#include "colour/colour.h"

// Declared, not included: a HitInfo refers to its Material.
struct HitInfo;
class Light;

// How a surface looks: the colour seen where a ray hits it, under a light.
class Material {
public:
    virtual ~Material() = default;
    virtual Colour shade(const HitInfo& hit, const Light& light) const = 0;
};
