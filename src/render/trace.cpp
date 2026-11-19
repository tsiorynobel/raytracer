#include "render/trace.h"

Colour trace(const Ray& ray, const Sphere& sphere, const Light& light) {
    std::optional<HitInfo> hit = sphere.hit(ray);
    if (hit) {
        return hit->material.shade(*hit, light);
    }
    return Colour(0, 0, 0);
}
