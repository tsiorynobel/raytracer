#include "render/trace.h"

Colour trace(const Ray& ray, const Sphere& sphere) {
    std::optional<HitInfo> hit = sphere.hit(ray);
    if (hit) {
        return hit->material.shade(ray);
    }
    return Colour(0, 0, 0);
}
