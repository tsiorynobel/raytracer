#pragma once
#include "colour/colour.h"
#include "geometry/ray.h"
#include "geometry/sphere.h"
#include "light/light.h"

Colour trace(const Ray& ray, const Sphere& sphere, const Light& light);
