#include <iostream>
#include <string>
#include "render/camera.h"
#include "colour/colour.h"
#include "geometry/sphere.h"
#include "image/image.h"
#include "output/png_saver.h"
#include "material/flat_shader.h"
#include "light/light.h"

int main() {
    // Position and configure the camera
    Camera camera(Vector(0, 0, -1), Vector(0, 0, 0), 2);

    // Describe the scene
    FlatShader yellow(Colour(1, 1, 0));
    Sphere sphere(Vector(0, 0, 9), 5, yellow);
    Light light(Vector(-10, 10, -5), Colour(1, 1, 1));

    // Render the scene into an image
    Image image = camera.render(sphere, light, 400, 300);

    // Save the rendered image to a file
    std::string path = "image.png";
    PngSaver saver;
    saver.save(image, path);
    std::cout << path << "\n";

    return 0;
}
