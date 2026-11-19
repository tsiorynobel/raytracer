#pragma once

#include "material/material.h"
#include "colour/colour.h"

// A matte surface: as bright as it faces the light (Lambert's cosine law).
class LambertShader : public Material {
private:
    Colour _colour;

public:
    explicit LambertShader(const Colour& colour);

    Colour shade(const HitInfo& hit, const Light& light) const override;
};
