#include "render/camera.h"

Camera::Camera(const Vector& eye, const Vector& screenCentre, double screenWidth)
    : _eye(eye), _screenCentre(screenCentre), _screenWidth(screenWidth) {}

Ray Camera::rayThroughCentre() const {
    return Ray(_eye, _screenCentre - _eye);
}

Ray Camera::rayThroughPixel(int column, int row, int imageWidth, int imageHeight) const {
    double pixelSize = _screenWidth / imageWidth;

    // Centre of the pixel; image rows go down, the world's y goes up.
    double x = ((column + 0.5) - imageWidth / 2.0) * pixelSize;
    double y = -((row + 0.5) - imageHeight / 2.0) * pixelSize;

    Vector pixel = _screenCentre + Vector(x, y, 0);
    return Ray(_eye, pixel - _eye);
}
