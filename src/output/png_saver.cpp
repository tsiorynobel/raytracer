#include "output/png_saver.h"
#include "lodepng.h"
#include <cmath>
#include <stdexcept>
#include <vector>

static unsigned char toByte(double value) {
    return static_cast<unsigned char>(std::lround(value * 255));
}

void PngSaver::save(const Image& image, const std::string& path) const {
    std::vector<unsigned char> bytes;
    bytes.reserve(image.width() * image.height() * 3);

    for (int row = 0; row < image.height(); ++row) {
        for (int column = 0; column < image.width(); ++column) {
            Colour colour = image.pixel(column, row);
            bytes.push_back(toByte(colour.r()));
            bytes.push_back(toByte(colour.g()));
            bytes.push_back(toByte(colour.b()));
        }
    }

    unsigned int error = lodepng::encode(path, bytes, image.width(), image.height(), LCT_RGB);
    if (error) {
        throw std::runtime_error(lodepng_error_text(error));
    }
}
