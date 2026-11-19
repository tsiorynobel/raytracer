#pragma once
#include "math/vector.h"
#include "geometry/ray.h"
#include "geometry/sphere.h"
#include "image/image.h"

class Camera {
private:
    Vector _eye;
    Vector _screenCentre;
    double _screenWidth;

public:
    Camera(const Vector& eye, const Vector& screenCentre, double screenWidth);

    Ray rayThroughPixel(int column, int row, int imageWidth, int imageHeight) const;

    Image render(const Sphere& sphere, const Vector& toLight, int width, int height) const;
};
