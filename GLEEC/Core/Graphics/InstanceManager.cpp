#include "InstanceManager.h"

namespace GLEEC::Graphics
{
    Instance InstanceManager::instance = {};

    void InstanceManager::createInstance()
    {
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        instance.instance = Internal::Graphics::vk::createInstance();
#endif
    }

    void InstanceManager::destroyInstance()
    {
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        Internal::Graphics::vk::destroyInstance(instance.instance);
#endif
    }
}
