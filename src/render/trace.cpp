#include "render/trace.h"

Colour trace(const Ray& ray, const Sphere& sphere, const Vector& toLight) {
    std::optional<Hit> hit = sphere.hit(ray);
    if (hit) {
        return hit->material.shade(hit->normal, toLight);
    }
    return Colour(0, 0, 0);
}
