#include "Load.h"

#define STB_IMAGE_IMPLEMENTATION
#include "STB/stb_image.h"

namespace GLEEC::Internal::Image
{
    inline Image loadImage(std::string_view filepath)
    {
        Image temp;
        int width, height, channels;

        temp.data = stbi_load(filepath.data(), &width, &height, &channels, 4);

        temp.width = width;
        temp.height = height;
        temp.channels = channels;

        return temp;
    }

    inline void destroyImage(Image& image)
    {
        stbi_image_free(image.data);
    }
}
