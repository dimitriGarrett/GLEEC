#include "MaterialManager.h"

namespace GLEEC::Graphics
{
    inline void ColorMaterial::bind()
    {
        MaterialManager::bindColorMaterial(this);
    }

    inline void TextureMaterial::bind()
    {
        MaterialManager::bindTextureMaterial(this);
    }

    inline uint32_t ColorMaterial::buffer(uint32_t a, uint32_t)
    {
        return a;
    }

    inline uint32_t TextureMaterial::buffer(uint32_t, uint32_t a)
    {
        return a;
    }

    void MaterialManager::bindColorMaterial(Material* material)
    {
        ColorMaterial& colorMaterial = *static_cast<ColorMaterial*>(material);

        math::vec4 col(material->diffuse, material->d);
        memcpy_s(colorMaterial.colorBuffer.buffer.map, sizeof(col), &col.x,
            sizeof(col));
    }

    void MaterialManager::bindTextureMaterial(Material* material)
    {
        // nop
    }
}
