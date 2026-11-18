#include "camera.h"

Camera::Camera(const Vector& eye, const Vector& screenCentre)
    : _eye(eye), _screenCentre(screenCentre) {}

Ray Camera::rayThroughCentre() const {
    return Ray(_eye, _screenCentre - _eye);
}
