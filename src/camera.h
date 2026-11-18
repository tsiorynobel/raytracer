#pragma once
#include "math/vector.h"
#include "ray.h"

class Camera {
private:
    Vector _eye;
    Vector _screenCentre;

public:
    Camera(const Vector& eye, const Vector& screenCentre);

    Ray rayThroughCentre() const;
};
