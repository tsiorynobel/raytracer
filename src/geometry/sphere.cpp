#include "geometry/sphere.h"
#include <cmath>

Sphere::Sphere(const Vector& centre, double radius, const Material& material)
    : _centre(centre), _radius(radius), _material(material) {}

const Material& Sphere::material() const { return _material; }

std::optional<HitInfo> Sphere::hit(const Ray& ray) const {
    Vector D = ray.direction();
    Vector L = ray.origin() - _centre;

    double a = D.dot(D);
    double b = 2.0 * D.dot(L);
    double c = L.dot(L) - _radius * _radius;

    double discriminant = b * b - 4.0 * a * c;
    if (discriminant < 0.0) {
        return std::nullopt;
    }

    double root = std::sqrt(discriminant);
    double nearT = (-b - root) / (2.0 * a);
    double farT = (-b + root) / (2.0 * a);

    double t = nearT > 0.0 ? nearT : farT;
    if (t <= 0.0) {
        return std::nullopt;
    }

    Vector point = ray.at(t);
    Vector normal = (point - _centre).normalised();
    return HitInfo{point, normal, _material};
}
