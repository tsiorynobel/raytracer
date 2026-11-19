#pragma once

#include <string>
#include "image/image.h"

class ImageSaver {
public:
    virtual ~ImageSaver() = default;
    // Writes the whole image to the file at path, or throws std::runtime_error.
    virtual void save(const Image& image, const std::string& path) const = 0;
};
