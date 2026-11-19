#pragma once

#include "material/material.h"
#include "colour/colour.h"

// The same colour everywhere, whatever the normal and the light: no shading.
class FlatShader : public Material {
private:
    Colour _colour;

public:
    explicit FlatShader(const Colour& colour);

    Colour shade(const Vector& normal, const Vector& toLight) const override;
};
