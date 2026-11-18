#include "render/trace.h"

Colour trace(const Ray& ray, const Sphere& sphere) {
    if (sphere.isHitBy(ray)) {
        return sphere.colour();
    }
    return Colour(0, 0, 0);
}
