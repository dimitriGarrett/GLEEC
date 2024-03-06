#pragma once

#include "math/utility/defines.h"

#include "Internal/Graphics/Backend.h"

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
#include "Internal/Graphics/vk/Format.h"
#endif

#include <array>

namespace GLEEC::Graphics::Renderer
{
    struct Vertex
    {
        // TODO: reorder as pos, uv.x, norm, uv.y?
        math::vec3 pos  = {};
        math::vec2 uv   = {};
        math::vec3 norm = {};

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        static constexpr uint32_t bindings = 1;
        static constexpr uint32_t attributes = 3;

        // all this code is taken from one of my old projects and bindings
        // have never been tested, and i forget what they are atp.
        // i hope it works cause im not gonna make sure
        // TODO: probably check if this works (much later)
        static constexpr std::array<VkVertexInputBindingDescription2EXT, bindings> bindingDescription()
        {
            std::array<VkVertexInputBindingDescription2EXT, bindings> descriptions = {};

            descriptions[0].sType =
                VK_STRUCTURE_TYPE_VERTEX_INPUT_BINDING_DESCRIPTION_2_EXT;
            descriptions[0].divisor = 1;
            descriptions[0].binding = 0;
            descriptions[0].stride = sizeof(math::vec3) * 2 + sizeof(math::vec2);

            descriptions[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

            return descriptions;
        }

        static constexpr std::array<VkVertexInputAttributeDescription2EXT, attributes * bindings> attributeDescription()
        {
            // attributes already a variable smh
            std::array<VkVertexInputAttributeDescription2EXT, attributes * bindings> fattributes = {};

            constexpr std::array<std::array<VkFormat, attributes>, bindings> formats = {
                {
                    VK_FORMAT_R32G32B32_SFLOAT,
                    VK_FORMAT_R32G32_SFLOAT,
                    VK_FORMAT_R32G32B32_SFLOAT,
                }
            };

            for (uint32_t binding = 0; binding < bindings; ++binding)
            {
                uint32_t offset = 0;
                for (uint32_t location = 0; location < attributes; ++location)
                {
                    VkVertexInputAttributeDescription2EXT& attribute =
                        fattributes[binding + location];
                    attribute.sType =
                        VK_STRUCTURE_TYPE_VERTEX_INPUT_ATTRIBUTE_DESCRIPTION_2_EXT;
                    attribute.binding = binding;
                    attribute.location = location;
                    attribute.format = formats[binding][location];

                    attribute.offset = offset;
                    offset += Internal::Graphics::vk::formatSize(attribute.format);
                }
            }

            return fattributes;
        }
#endif
    };
}
