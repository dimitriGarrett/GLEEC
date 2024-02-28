#include "InstanceLayers.h"

namespace GLEEC::Internal::Graphics::vk
{
    std::vector<const char*> InstanceLayerProperties::requestedLayers()
    {
// only turn on validation layers if i am debugging (they get annoying and slow)
#if GLEEC_DEBUG
        return { "VK_LAYER_KHRONOS_validation" };
#else
        return {};
#endif
    }
}
