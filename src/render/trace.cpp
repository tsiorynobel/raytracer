#include "render/trace.h"

Colour trace(const Ray& ray, const Sphere& sphere) {
    if (sphere.isHitBy(ray)) {
        return sphere.material().shade(ray);
    }
    return Colour(0, 0, 0);
}
