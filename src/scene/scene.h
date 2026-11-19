#pragma once
#include <memory>
#include <optional>
#include <vector>
#include "math/vector.h"
#include "geometry/ray.h"
#include "geometry/hit.h"
#include "geometry/shape.h"

// What the camera looks at: the shapes, and the sun that lights them.
// The scene owns its shapes; their materials must outlive it.
class Scene {
private:
    Vector _toLight;
    std::vector<std::unique_ptr<Shape>> _shapes;

public:
    // toLight is the direction to the sun; it is made a unit vector.
    explicit Scene(const Vector& toLight);

    const Vector& toLight() const;
    void add(std::unique_ptr<Shape> shape);

    // The hit with the smallest t among all shapes, or nothing.
    std::optional<Hit> nearestHit(const Ray& ray) const;
};
