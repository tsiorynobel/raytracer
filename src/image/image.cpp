#include "image/image.h"

Image::Image(int width, int height)
    : _width(width), _height(height), _pixels(width * height, Colour(0, 0, 0)) {}

int Image::width() const { return _width; }
int Image::height() const { return _height; }

// Pixels are stored row by row, from the top-left corner.
int Image::index(int column, int row) const {
    return row * _width + column;
}

Colour Image::pixel(int column, int row) const {
    return _pixels[index(column, row)];
}

void Image::setPixel(int column, int row, const Colour& colour) {
    _pixels[index(column, row)] = colour;
}
