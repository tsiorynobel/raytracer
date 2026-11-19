#include "render/camera.h"
#include "render/trace.h"

Camera::Camera(const Vector& eye, const Vector& screenCentre, double screenWidth)
    : _eye(eye), _screenCentre(screenCentre), _screenWidth(screenWidth) {}

Ray Camera::rayThroughPixel(int column, int row, int imageWidth, int imageHeight) const {
    double pixelSize = _screenWidth / imageWidth;

    // Centre of the pixel; image rows go down, the world's y goes up.
    double x = ((column + 0.5) - imageWidth / 2.0) * pixelSize;
    double y = -((row + 0.5) - imageHeight / 2.0) * pixelSize;

    Vector pixel = _screenCentre + Vector(x, y, 0);
    return Ray(_eye, pixel - _eye);
}

Image Camera::render(const Sphere& sphere, const Vector& toLight, int width, int height) const {
    Image image(width, height);

    for (int row = 0; row < height; ++row) {
        for (int column = 0; column < width; ++column) {
            Ray ray = rayThroughPixel(column, row, width, height);
            image.setPixel(column, row, trace(ray, sphere, toLight));
        }
    }

    return image;
}
