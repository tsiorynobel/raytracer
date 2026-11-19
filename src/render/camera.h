#pragma once
#include "math/vector.h"
#include "geometry/ray.h"
#include "geometry/sphere.h"
#include "render/image.h"

class Camera {
private:
    Vector _eye;
    Vector _screenCentre;
    double _screenWidth;

public:
    Camera(const Vector& eye, const Vector& screenCentre, double screenWidth);

    Ray rayThroughCentre() const;
    Ray rayThroughPixel(int column, int row, int imageWidth, int imageHeight) const;

    void render(const Sphere& sphere, Image& image) const;
};
