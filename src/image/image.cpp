#include "image/image.h"

Image::Image(int width, int height)
    : _width(width), _height(height), _pixels(width * height, Colour(0, 0, 0)) {}

int Image::width() const { return _width; }
int Image::height() const { return _height; }

Colour Image::pixel(int column, int row) const {
    return _pixels[row * _width + column];
}

void Image::setPixel(int column, int row, const Colour& colour) {
    _pixels[row * _width + column] = colour;
}
