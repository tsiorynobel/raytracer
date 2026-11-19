#pragma once
#include "math/vector.h"

class Ray {
private:
    Vector _origin;
    Vector _direction;

public:
    Ray(const Vector& origin, const Vector& direction);

    const Vector& origin() const;
    const Vector& direction() const;
    // The point origin + t * direction.
    Vector at(double t) const;
};
