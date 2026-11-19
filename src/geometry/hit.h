#pragma once

#include "math/vector.h"
#include "material/material.h"

// Where a ray hits a surface: at which t along the ray, the point, the unit
// normal there, and the material of the surface. The material must outlive the hit.
struct Hit {
    double t;
    Vector point;
    Vector normal;
    const Material& material;
};
