#pragma once

#include <string>

namespace GLEEC::Caching
{
    enum ResourceType
    {
        NONE = 0,
        SHADER = 1,
        DESCRIPTOR_SET_LAYOUT = 2,
        MODEL = 3,
    };

    namespace detail
    {
        inline std::string filepathPrefix(ResourceType resource)
        {
            switch (resource)
            {
            case SHADER: return "GCVKSB-"; // GLEEC VULKAN SHADER BINARY
            case DESCRIPTOR_SET_LAYOUT: return "GCVKDSLB-"; // GLEEC VULKAN DESCRIPTOR SET LAYOUT BINDINGS
            case MODEL: return "GCMD-"; // GLEEC MODEL
            case NONE: return "GCNN-"; // GLEEC NONE
            default: return "GCUK-";  // GLEEC UNKNOWN
            }
        }
    }
}
