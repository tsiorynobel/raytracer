#include <iostream>
#include "render/camera.h"
#include "colour/colour.h"
#include "geometry/sphere.h"
#include "image/image.h"
#include "output/png_saver.h"

int main() {
    // Position and configure the camera
    Camera camera(Vector(0, 0, -1), Vector(0, 0, 0), 2.0);

    // Describe the scene
    Sphere sphere(Vector(0, 0, 9), 5, Colour(1, 0, 0));

    // Size of the image
    const int imageWidth = 512;
    const int imageHeight = 512;

    // Render the scene into an image
    Image image = camera.render(sphere, imageWidth, imageHeight);

    // Save the rendered image to a file
    PngSaver saver;
    saver.save(image, "output.png");
    std::cout << "Saved output.png (" << imageWidth << " x " << imageHeight << ")\n";

    return 0;
}
