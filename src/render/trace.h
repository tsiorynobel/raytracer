#pragma once
#include "colour/colour.h"
#include "geometry/ray.h"
#include "scene/scene.h"

// The colour seen along a ray: the nearest hit's material lit by the sun, or black.
Colour trace(const Ray& ray, const Scene& scene);
