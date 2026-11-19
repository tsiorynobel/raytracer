#pragma once

#include <string>
#include "output/image_saver.h"

class PngSaver : public ImageSaver {
public:
    void save(const Image& image, const std::string& path) const override;
};
