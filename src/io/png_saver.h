#pragma once

#include <string>
#include "io/image_saver.h"

class PngSaver : public ImageSaver {
public:
    void save(Image& image, const std::string& path) override;
};
