#pragma once

#include <string>
#include "output/image_saver.h"

class PngSaver : public ImageSaver {
public:
    void save(Image& image, const std::string& path) override;
};
