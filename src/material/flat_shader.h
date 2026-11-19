#pragma once

#include "material/material.h"
#include "colour/colour.h"

// The same colour everywhere, whatever the hit and the light: no shading.
class FlatShader : public Material {
private:
    Colour _colour;

public:
    explicit FlatShader(const Colour& colour);

    Colour shade(const HitInfo& hit, const Light& light) const override;
};
