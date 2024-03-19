#pragma once

#include "Config/Export.h"
#include "Instance.h"
#include "Internal/Log/Log.h"

#include "Internal/Graphics/Backend.h"

#if GLEEC_GRAPHICS_WINDOW_BACKEND == GRAPHICS_WINDOW_BACKEND_GLFW
#include "Internal/Graphics/Backends/glfw.h"
#endif

#include <array>
#include <string.h> // memcpy_s

namespace GLEEC::Internal::Graphics::vk
{
    using PhysicalDevice = VkPhysicalDevice;

    inline std::vector<PhysicalDevice> enumeratePhysicalDevices(VkInstance instance)
    {
        uint32_t count = 0;
        CHECK_VK(vkEnumeratePhysicalDevices(instance, &count, nullptr));

        std::vector<PhysicalDevice> physicalDevices(count);
        CHECK_VK(vkEnumeratePhysicalDevices(instance, &count, physicalDevices.data()));

        return physicalDevices;
    }

    GLEEC_API_EXTERN bool physicalDeviceSuitable(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);

    inline PhysicalDevice bestPhysicalDevice(VkInstance instance, VkSurfaceKHR surface)
    {
        std::vector<PhysicalDevice> physicalDevices = enumeratePhysicalDevices(instance);

        if (physicalDevices.empty())
        {
            LOG_ERROR("Vulkan: no GPUs supporting vk!");

            return {};
        }

        if (physicalDevices.size() == 1)
        {
            LOG_INFO("Vulkan: only one GPU present with vk support, assuming it works!");

            return physicalDevices.front();
        }

        for (const PhysicalDevice& physicalDevice : physicalDevices)
        {
            if (physicalDeviceSuitable(physicalDevice, surface))
            {
                LOG_INFO("Vulkan: found suitable GPU with surface capabilities!");

                return physicalDevice;
            }
        }

        LOG_INFO("Vulkan: no suitable GPU found, returning the first and hoping for the best!");

        return physicalDevices.front();
    }

    inline PhysicalDevice bestPhysicalDevice(VkInstance instance)
    {
        std::vector<PhysicalDevice> physicalDevices = enumeratePhysicalDevices(instance);

        if (physicalDevices.empty())
        {
            LOG_ERROR("Vulkan: no GPUs supporting vk!");

            return {};
        }

        return physicalDevices.front();
    }

    // will create a dummy surface to test the capabilities 
#if GLEEC_GRAPHICS_WINDOW_BACKEND == GRAPHICS_WINDOW_BACKEND_GLFW
    GLEEC_API_EXTERN PhysicalDevice bestPhysicalDevice(VkInstance instance, GLFWwindow* window);
#endif

    inline std::vector<VkQueueFamilyProperties> getPhysicalDeviceQueueFamilyProperties(VkPhysicalDevice physicalDevice)
    {
        uint32_t count = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &count, nullptr);

        std::vector<VkQueueFamilyProperties> properties(count);
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &count, properties.data());

        return properties;
    }

    inline VkSurfaceCapabilitiesKHR getPhysicalDeviceSurfaceCapabilities(VkPhysicalDevice physicalDevice,
        VkSurfaceKHR surface)
    {
        VkSurfaceCapabilitiesKHR caps = {};
        CHECK_VK(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface, &caps));
        return caps;
    }

    inline VkSurfaceCapabilities2KHR getPhysicalDeviceSurfaceCapabilities2(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, VkPresentModeKHR presentMode, void* pNext = nullptr)
    {
        VkSurfaceCapabilities2KHR caps = {
            VK_STRUCTURE_TYPE_SURFACE_CAPABILITIES_2_KHR
        };

        caps.pNext = pNext;

        VkPhysicalDeviceSurfaceInfo2KHR surfaceInfo = {
            VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SURFACE_INFO_2_KHR
        };
        
        VkSurfacePresentModeEXT presentInfo = {
            VK_STRUCTURE_TYPE_SURFACE_PRESENT_MODE_EXT
        };

        presentInfo.presentMode = presentMode;

        surfaceInfo.pNext = &presentInfo;

        surfaceInfo.surface = surface;

        CHECK_VK(vkGetPhysicalDeviceSurfaceCapabilities2KHR(physicalDevice, &surfaceInfo, &caps));

        return caps;
    }

    inline std::vector<VkPresentModeKHR> getPhysicalDeviceSurfacePresentModes(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface)
    {
        uint32_t count = 0;
        CHECK_VK(vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &count, nullptr));

        std::vector<VkPresentModeKHR> presentModes(count);
        CHECK_VK(vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &count, presentModes.data()));

        return presentModes;
    }

    inline std::vector<VkSurfaceFormatKHR> getPhysicalDeviceSurfaceFormats(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface)
    {
        uint32_t count = 0;
        CHECK_VK(vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &count, nullptr));

        std::vector<VkSurfaceFormatKHR> surfaceFormats(count);
        CHECK_VK(vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &count, surfaceFormats.data()));

        return surfaceFormats;
    }

    inline VkQueueFamilyProperties getPhysicalDeviceQueueFamilyPropertiesFromFlags(VkPhysicalDevice physicalDevice, VkQueueFlags flags)
    {
        for (const VkQueueFamilyProperties& queueFamilyProperties : getPhysicalDeviceQueueFamilyProperties(physicalDevice))
        {
            if (queueFamilyProperties.queueFlags & flags)
            {
                return queueFamilyProperties;
            }
        }

        return {};
    }

    inline uint32_t getPhysicalDeviceQueueFamilyIndexFromFlags(VkPhysicalDevice physicalDevice, VkQueueFlags flags)
    {
        const std::vector<VkQueueFamilyProperties> queueFamilyProperties = getPhysicalDeviceQueueFamilyProperties(physicalDevice);

        const size_t size = queueFamilyProperties.size();
        for (size_t i = 0; i < size; ++i)
        {
            if (queueFamilyProperties[i].queueFlags & flags) return i;
        }

        return -1;
    }

    inline VkQueueFamilyProperties getPhysicalDeviceGraphicsQueueFamilyProperties(VkPhysicalDevice physicalDevice)
    {
        return getPhysicalDeviceQueueFamilyPropertiesFromFlags(physicalDevice, VK_QUEUE_GRAPHICS_BIT);
    }

    inline VkQueueFamilyProperties getPhysicalDeviceComputeQueueFamilyProperties(VkPhysicalDevice physicalDevice)
    {
        return getPhysicalDeviceQueueFamilyPropertiesFromFlags(physicalDevice, VK_QUEUE_COMPUTE_BIT);
    }

    inline VkQueueFamilyProperties getPhysicalDeviceTransferQueueFamilyProperties(VkPhysicalDevice physicalDevice)
    {
        return getPhysicalDeviceQueueFamilyPropertiesFromFlags(physicalDevice, VK_QUEUE_TRANSFER_BIT);
    }

    inline uint32_t getPhysicalDeviceGraphicsQueueFamilyIndex(VkPhysicalDevice physicalDevice)
    {
        return getPhysicalDeviceQueueFamilyIndexFromFlags(physicalDevice, VK_QUEUE_GRAPHICS_BIT);
    }

    inline uint32_t getPhysicalDeviceComputeQueueFamilyIndex(VkPhysicalDevice physicalDevice)
    {
        return getPhysicalDeviceQueueFamilyIndexFromFlags(physicalDevice, VK_QUEUE_COMPUTE_BIT);
    }

    inline uint32_t getPhysicalDeviceTransferQueueFamilyIndex(VkPhysicalDevice physicalDevice)
    {
        return getPhysicalDeviceQueueFamilyIndexFromFlags(physicalDevice, VK_QUEUE_TRANSFER_BIT);
    }

    inline bool getPhysicalDeviceSurfaceSupport(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, uint32_t queueFamilyIndex)
    {
        VkBool32 supported = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, queueFamilyIndex, surface, &supported);
        return supported;
    }

    inline VkQueueFamilyProperties getPhysicalDevicePresentQueueFamilyProperties(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface)
    {
        uint32_t i = 0;
        for (const VkQueueFamilyProperties& props : getPhysicalDeviceQueueFamilyProperties(physicalDevice))
        {
            if (getPhysicalDeviceSurfaceSupport(physicalDevice, surface, i++))
            {
                return props;
            }
        }

        return {};
    }

    inline uint32_t getPhysicalDevicePresentQueueFamilyIndex(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface)
    {
        uint32_t size = getPhysicalDeviceQueueFamilyProperties(physicalDevice).size();
        for (uint32_t i = 0; i < size; ++i)
        {
            if (getPhysicalDeviceSurfaceSupport(physicalDevice, surface, i))
            {
                return i;
            }
        }

        return -1;
    }

    inline bool getPhysicalDeviceGraphicsQueueSurfaceSupport(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface)
    {
        return getPhysicalDeviceSurfaceSupport(physicalDevice, surface, getPhysicalDeviceGraphicsQueueFamilyIndex(physicalDevice));
    }

    inline VkPhysicalDeviceProperties getPhysicalDeviceProperties(VkPhysicalDevice physicalDevice)
    {
        VkPhysicalDeviceProperties properties = {};
        vkGetPhysicalDeviceProperties(physicalDevice, &properties);
        return properties;
    }

    inline VkPhysicalDeviceProperties2 getPhysicalDeviceProperties2(VkPhysicalDevice physicalDevice, void* pNext = nullptr)
    {
        VkPhysicalDeviceProperties2 properties = {
            VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2
        };

        properties.pNext = pNext;

        vkGetPhysicalDeviceProperties2(physicalDevice, &properties);
        return properties;
    }

    inline VkPhysicalDeviceLimits getPhysicalDeviceLimits(VkPhysicalDevice physicalDevice)
    {
        return getPhysicalDeviceProperties(physicalDevice).limits;
    }

    inline VkPhysicalDeviceSparseProperties getPhysicalDeviceSparseProperties(VkPhysicalDevice physicalDevice)
    {
        return getPhysicalDeviceProperties(physicalDevice).sparseProperties;
    }

    inline VkPhysicalDeviceFeatures getPhysicalDeviceFeatures(VkPhysicalDevice physicalDevice)
    {
        VkPhysicalDeviceFeatures features = {};
        vkGetPhysicalDeviceFeatures(physicalDevice, &features);
        return features;
    }

    inline VkPhysicalDeviceFeatures2 getPhysicalDeviceFeatures2(VkPhysicalDevice physicalDevice, void* pNext = nullptr)
    {
        VkPhysicalDeviceFeatures2 features = {
            VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2
        };

        features.pNext = pNext;

        vkGetPhysicalDeviceFeatures2(physicalDevice, &features);
        return features;
    }

    inline VkPhysicalDeviceMemoryProperties getPhysicalDeviceMemoryProperties(VkPhysicalDevice physicalDevice)
    {
        VkPhysicalDeviceMemoryProperties properties = {};
        vkGetPhysicalDeviceMemoryProperties(physicalDevice, &properties);
        return properties;
    }

    inline bool getPhysicalDeviceSupportsAnisotropy(VkPhysicalDevice physicalDevice)
    {
        return getPhysicalDeviceFeatures(physicalDevice).samplerAnisotropy;
    }

    namespace properties
    {
        inline uint32_t getPhysicalDeviceApiVersion(VkPhysicalDevice physicalDevice)
        {
            return getPhysicalDeviceProperties(physicalDevice).apiVersion;
        }

        inline uint32_t getPhysicalDeviceDriverVersion(VkPhysicalDevice physicalDevice)
        {
            return getPhysicalDeviceProperties(physicalDevice).driverVersion;
        }

        inline uint32_t getPhysicalDeviceVendorID(VkPhysicalDevice physicalDevice)
        {
            return getPhysicalDeviceProperties(physicalDevice).vendorID;
        }

        inline uint32_t getPhysicalDeviceID(VkPhysicalDevice physicalDevice)
        {
            return getPhysicalDeviceProperties(physicalDevice).deviceID;
        }

        inline VkPhysicalDeviceType getPhysicalDeviceType(VkPhysicalDevice physicalDevice)
        {
            return getPhysicalDeviceProperties(physicalDevice).deviceType;
        }

        inline const char* getPhysicalDeviceTypeString(VkPhysicalDevice physicalDevice)
        {
            VkPhysicalDeviceType type = getPhysicalDeviceProperties(physicalDevice).deviceType;

            switch (type)
            {
            default:
            case VK_PHYSICAL_DEVICE_TYPE_OTHER: return "Unknown GPU type!";
            case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU: return "Integrated GPU";
            case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU: return "Discrete GPU";
            case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU: return "Virtual GPU";
            case VK_PHYSICAL_DEVICE_TYPE_CPU: return "CPU GPU";
            }
        }

        inline std::string getPhysicalDeviceName(VkPhysicalDevice physicalDevice)
        {
            std::string str = "";
            
            for (char c : getPhysicalDeviceProperties(physicalDevice).deviceName)
            {
                str.push_back(c);
            }

            return str;
        }

        inline std::array<uint8_t, VK_UUID_SIZE> getPhysicalDevicePipelineCacheUUID(VkPhysicalDevice physicalDevice)
        {
            std::array<uint8_t, VK_UUID_SIZE> cacheUUID = {};
            memcpy_s(cacheUUID.data(), VK_UUID_SIZE, getPhysicalDeviceProperties(physicalDevice).pipelineCacheUUID, VK_UUID_SIZE);
            return cacheUUID;
        }

        inline std::string getPhysicalDeviceDriverName(VkPhysicalDevice physicalDevice)
        {
            std::string str = "";

            VkPhysicalDeviceDriverProperties properties = {
                VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DRIVER_PROPERTIES
            };

            getPhysicalDeviceProperties2(physicalDevice, &properties);
            for (char c : properties.driverName)
            {
                str.push_back(c);
            }

            return str;
        }

        inline std::string getPhysicalDeviceDriverInfo(VkPhysicalDevice physicalDevice)
        {
            std::string str = "";

            VkPhysicalDeviceDriverProperties properties = {
                VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DRIVER_PROPERTIES
            };

            getPhysicalDeviceProperties2(physicalDevice, &properties);
            for (char c : properties.driverInfo)
            {
                str.push_back(c);
            }

            return str;
        }
    }

    inline void printPhysicalDeviceInformation(VkPhysicalDevice physicalDevice)
    {
        LOG_INFO("Vulkan: physicalDevice \"{}\"", static_cast<void*>(physicalDevice));

        LOG_INFO("apiVersion:    {}", properties::getPhysicalDeviceApiVersion(physicalDevice));
        LOG_INFO("driverVersion: {}", properties::getPhysicalDeviceDriverVersion(physicalDevice));
        LOG_INFO("vendorID:      {}", properties::getPhysicalDeviceVendorID(physicalDevice));
        LOG_INFO("deviceID:      {}", properties::getPhysicalDeviceID(physicalDevice));
        LOG_INFO("deviceType:    {}", properties::getPhysicalDeviceTypeString(physicalDevice));
        LOG_INFO("deviceName:   \"{}\"", properties::getPhysicalDeviceName(physicalDevice));
        LOG_INFO("driverName:   \"{}\"", properties::getPhysicalDeviceDriverName(physicalDevice));
        LOG_INFO("driverInfo:   \"{}\"", properties::getPhysicalDeviceDriverInfo(physicalDevice));
    }
}
