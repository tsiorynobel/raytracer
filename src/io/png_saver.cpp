#include "io/png_saver.h"
#include "lodepng.h"
#include <stdexcept>

void PngSaver::save(Image& image, const std::string& path) {
    const unsigned int width = image.width();
    const unsigned int height = image.height();

    std::vector<unsigned char> pixels;
    pixels.reserve(width * height * 4);

    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x) {
            Colour c = image.pixel(x, y);
            pixels.push_back(static_cast<unsigned char>(c.r() * 255));
            pixels.push_back(static_cast<unsigned char>(c.g() * 255));
            pixels.push_back(static_cast<unsigned char>(c.b() * 255));
            pixels.push_back(255);
        }
    }

    unsigned int error = lodepng::encode(path, pixels, width, height);
    if (error) {
        throw std::runtime_error(lodepng_error_text(error));
    }
}
