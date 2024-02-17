#pragma once

#include "Internal/Image/Load.h"

namespace GLEEC::Image
{
    struct Image
    {
        Internal::Image::Image image = {};

        decltype(Internal::Image::Image::data)& data = image.data;
        decltype(Internal::Image::Image::width)& width = image.width;
        decltype(Internal::Image::Image::height)& height = image.height;

        Image() = default;
        Image(std::string_view filepath)
            : image(Internal::Image::loadImage(filepath))
        {
        }

        ~Image()
        {
            destroyImage(image);
        }
    };
}
