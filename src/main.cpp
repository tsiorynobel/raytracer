#include <iostream>
#include "render/camera.h"
#include "colour/colour.h"
#include "geometry/sphere.h"

int main() {
    Camera camera(Vector(0, 0, -1), Vector(0, 0, 0));
    Sphere sphere(Vector(0, 0, 9), 5, Colour(1, 0, 0));

    Ray ray = camera.rayThroughCentre();
    Colour pixel = sphere.isHitBy(ray) ? sphere.colour() : Colour(0, 0, 0);

    std::cout << "(" << pixel.r() << ", " << pixel.g() << ", " << pixel.b() << ")\n";
    return 0;
}
