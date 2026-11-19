#pragma once
#include <optional>
#include "math/vector.h"
#include "geometry/ray.h"
#include "geometry/hit.h"
#include "material/material.h"

class Sphere {
private:
    Vector _centre;
    double _radius;
    const Material& _material;

public:
    // The sphere refers to its material: the material must live at least as long.
    Sphere(const Vector& centre, double radius, const Material& material);
    // A temporary material would be destroyed at once and leave a dangling reference.
    Sphere(const Vector& centre, double radius, const Material&& material) = delete;

    const Material& material() const;
    // The nearest point in front of the ray origin (t > 0), or nothing on a miss.
    std::optional<Hit> hit(const Ray& ray) const;
};
