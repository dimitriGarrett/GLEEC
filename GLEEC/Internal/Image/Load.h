#pragma once

#include "Config/Export.h"
#include "Image.h"

#include <string_view>

namespace GLEEC::Internal::Image
{
    GLEEC_API_EXTERN Image loadImage(std::string_view filepath);
    GLEEC_API_EXTERN void destroyImage(Image& image);
}
