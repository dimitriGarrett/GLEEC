#include "GPUManager.h"

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
#include "Internal/Graphics/vk/RequestedDeviceQueue.h"
#include "Internal/Graphics/vk/Surface.h"
#include "Internal/Graphics/vk/Extensions.h"
#endif

#include "InstanceManager.h"
#include "Core/Window/WindowManager.h"

namespace GLEEC::Graphics
{
    GPU GPUManager::activeGPU = {};

    void GPUManager::selectGPU()
    {
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        Internal::Graphics::vk::Surface& surface = Window::WindowManager::windows.front().surface;

        activeGPU.device.physicalDevice = Internal::Graphics::vk::bestPhysicalDevice(
            InstanceManager::instance.instance, surface);

        // probably a nop anyways but why not?
#if GLEEC_DEBUG
        Internal::Graphics::vk::printPhysicalDeviceInformation(
            activeGPU.device.physicalDevice);
#endif

        activeGPU.device.device = Internal::Graphics::vk::createDevice(
            activeGPU.device.physicalDevice,
            Internal::Graphics::vk::defaultPreparedQueuesForDevice(
                activeGPU.device.physicalDevice, surface));

        Internal::Graphics::vk::loadDeviceExtensions(activeGPU.device.device);

        activeGPU.graphicsQueue = Internal::Graphics::vk::getDeviceGraphicsQueue(activeGPU.device);
        activeGPU.presentQueue = Internal::Graphics::vk::getDevicePresentQueue(activeGPU.device, Window::WindowManager::windows.front().surface);

        activeGPU.allocator = Internal::Graphics::vk::createAllocator(InstanceManager::instance.instance, activeGPU.device.physicalDevice, activeGPU.device.device);
#endif
    }

    void GPUManager::closeGPU()
    {
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        Internal::Graphics::vk::destroyAllocator(activeGPU.allocator);
        Internal::Graphics::vk::destroyDevice(activeGPU.device);
#endif
    }
}
