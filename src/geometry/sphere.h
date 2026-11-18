#pragma once
#include "math/vector.h"
#include "colour/colour.h"
#include "geometry/ray.h"

class Sphere {
private:
    Vector _centre;
    double _radius;
    Colour _colour;

public:
    Sphere(const Vector& centre, double radius, const Colour& colour);

    const Colour& colour() const;
    bool isHitBy(const Ray& ray) const;
};
