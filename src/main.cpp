#include <iostream>
#include <string>
#include "render/camera.h"
#include "colour/colour.h"
#include "geometry/sphere.h"
#include "image/image.h"
#include "output/png_saver.h"

int main() {
    // Position and configure the camera
    Camera camera(Vector(0, 0, -1), Vector(0, 0, 0), 2);

    // Describe the scene
    Sphere sphere(Vector(0, 0, 9), 5, Colour(1, 0, 0));

    // Render the scene into an image
    Image image = camera.render(sphere, 400, 300);

    // Save the rendered image to a file
    std::string path = "image.png";
    PngSaver saver;
    saver.save(image, path);
    std::cout << path << "\n";

    return 0;
}
