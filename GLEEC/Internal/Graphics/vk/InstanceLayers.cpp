#include "InstanceLayers.h"

namespace GLEEC::Internal::Graphics::vk
{
    std::vector<const char*> InstanceLayerProperties::requestedLayers()
    {
// only turn on validation layers if i am debugging (they get annoying and slow)
        return {
#if GLEEC_DEBUG
            "VK_LAYER_KHRONOS_validation",
#endif
            "VK_LAYER_KHRONOS_shader_object",
        };
    }
}
