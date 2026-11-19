#pragma once
#include <optional>
#include "math/vector.h"
#include "geometry/ray.h"
#include "geometry/hit.h"
#include "geometry/shape.h"
#include "material/material.h"

// An infinite flat surface through a point, facing its normal.
class Plane : public Shape {
private:
    Vector _point;
    Vector _normal;
    const Material& _material;

public:
    // The normal is made a unit vector. The plane refers to its material:
    // the material must live at least as long.
    Plane(const Vector& point, const Vector& normal, const Material& material);
    // A temporary material would be destroyed at once and leave a dangling reference.
    Plane(const Vector& point, const Vector& normal, const Material&& material) = delete;

    std::optional<Hit> hit(const Ray& ray) const override;
};
