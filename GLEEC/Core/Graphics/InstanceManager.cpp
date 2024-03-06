#include "InstanceManager.h"

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
#include "Internal/Graphics/vk/Extensions.h"
#endif

namespace GLEEC::Graphics
{
    Instance InstanceManager::instance = {};

    void InstanceManager::createInstance()
    {
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        instance.instance = Internal::Graphics::vk::createInstance();

        Internal::Graphics::vk::loadInstanceExtensions(instance.instance);
#endif
    }

    void InstanceManager::destroyInstance()
    {
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        Internal::Graphics::vk::destroyInstance(instance.instance);
#endif
    }
}
