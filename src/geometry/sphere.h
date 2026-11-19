#pragma once
#include "math/vector.h"
#include "geometry/ray.h"
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
    bool isHitBy(const Ray& ray) const;
};
