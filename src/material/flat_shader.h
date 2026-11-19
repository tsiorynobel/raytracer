#pragma once

#include "material/material.h"
#include "colour/colour.h"

// The same colour everywhere, whatever the ray: no light, no shadow.
class FlatShader : public Material {
private:
    Colour _colour;

public:
    explicit FlatShader(const Colour& colour);

    Colour shade(const Ray& ray) const override;
};
