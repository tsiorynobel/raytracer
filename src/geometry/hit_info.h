#pragma once

#include "math/vector.h"
#include "material/material.h"

// Where a ray hits a surface: the point, the unit normal there, and the
// material of the surface. The material must outlive the hit.
struct HitInfo {
    Vector point;
    Vector normal;
    const Material& material;
};
