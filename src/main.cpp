#include <iostream>
#include <memory>
#include <string>
#include "render/camera.h"
#include "colour/colour.h"
#include "geometry/sphere.h"
#include "geometry/plane.h"
#include "scene/scene.h"
#include "image/image.h"
#include "output/png_saver.h"
#include "material/lambert_shader.h"

int main() {
    // Position and configure the camera
    Camera camera(Vector(0, 0, -1), Vector(0, 0, 0), 2);

    // The materials live longer than the scene that uses them
    LambertShader yellow(Colour(1, 1, 0));
    LambertShader grey(Colour(0.8, 0.8, 0.8));

    // Describe the scene: the sun up and to the left, a ball on a floor
    Scene scene(Vector(-1, 1, -1));
    scene.add(std::make_unique<Sphere>(Vector(0, 0, 9), 5, yellow));
    scene.add(std::make_unique<Plane>(Vector(0, -5, 0), Vector(0, 1, 0), grey));

    // Render the scene into an image
    Image image = camera.render(scene, 400, 300);

    // Save the rendered image to a file
    std::string path = "image.png";
    PngSaver saver;
    saver.save(image, path);
    std::cout << path << "\n";

    return 0;
}
