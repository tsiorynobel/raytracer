#pragma once
#include "colour/colour.h"
#include "geometry/ray.h"
#include "geometry/sphere.h"

// toLight: the unit direction to the sun.
Colour trace(const Ray& ray, const Sphere& sphere, const Vector& toLight);
