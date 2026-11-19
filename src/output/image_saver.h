#pragma once

#include <string>
#include "image/image.h"

class ImageSaver {
public:
    virtual ~ImageSaver() = default;
    virtual void save(const Image& image, const std::string& path) const = 0;
};
