#pragma once

#include <optional>
#include "geometry/hit.h"
#include "geometry/ray.h"

// Anything a ray can hit. A new shape is a new class behind this interface.
class Shape {
public:
    virtual ~Shape() = default;

    // The nearest hit in front of the ray origin (t > 0), with a unit normal
    // pointing out of the surface, or nothing on a miss.
    virtual std::optional<Hit> hit(const Ray& ray) const = 0;
};
