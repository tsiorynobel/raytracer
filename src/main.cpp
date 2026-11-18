#include <iostream>
#include "render/camera.h"
#include "colour/colour.h"
#include "geometry/sphere.h"
#include "render/image.h"
#include "render/trace.h"
#include "io/png_saver.h"

int main() {
    const int imageWidth = 512;
    const int imageHeight = 512;

    Camera camera(Vector(0, 0, -1), Vector(0, 0, 0), 2.0);
    Sphere sphere(Vector(0, 0, 9), 5, Colour(1, 0, 0));

    Image image(imageWidth, imageHeight);

    for (int row = 0; row < imageHeight; ++row) {
        for (int column = 0; column < imageWidth; ++column) {
            Ray ray = camera.rayThroughPixel(column, row, imageWidth, imageHeight);
            image.setPixel(column, row, trace(ray, sphere));
        }
    }

    PngSaver saver;
    saver.save(image, "output.png");
    std::cout << "Saved output.png (" << imageWidth << " x " << imageHeight << ")\n";

    return 0;
}
