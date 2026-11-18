#pragma once

#include <string>
#include "render/image.h"

class ImageSaver {
public:
    virtual ~ImageSaver() = default;
    virtual void save(Image& image, const std::string& path) = 0;
};
