#pragma once

#include "colour/colour.h"
#include "geometry/ray.h"

// How a surface looks: the colour seen along a ray that hits it.
class Material {
public:
    virtual ~Material() = default;
    virtual Colour shade(const Ray& ray) const = 0;
};
