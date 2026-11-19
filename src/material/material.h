#pragma once

#include "colour/colour.h"
#include "math/vector.h"

// How a surface takes light. A strategy: each way of shading is its own class
// (FlatShader, LambertShader), and a shape only knows it has a Material.
class Material {
public:
    virtual ~Material() = default;

    // The colour seen for a surface normal and the direction to the light.
    // normal and toLight must be unit vectors.
    virtual Colour shade(const Vector& normal, const Vector& toLight) const = 0;
};
