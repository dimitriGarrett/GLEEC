#pragma once

#include "Internal/Log/Log.h"

#include <vulkan/vulkan.h>

#include "CHECK_VK.h"
#include <utility>

namespace GLEEC::Internal::Graphics::vk
{
    template <typename T>
    bool procAddressExists(std::string_view name, T* ptr)
    {
#if GLEEC_DEBUG
        if (ptr) return true;

        LOG_WARNING("Vulkan: failed to call ProcAddress func: {}, it was nullptr!", name);

        return false;
#else
        return ptr;
#endif
    }

    template <typename T, typename... Args>
    auto callProcAddress(std::string_view name, T* ptr, Args&&... args)
    {
        if (procAddressExists(name, ptr))
            return ptr(std::forward<Args>(args)...);
    }

    template <typename T, typename... Args>
    VkResult callProcAddress(std::string_view name, T* ptr, Args&&... args)
        requires std::is_same_v<decltype(ptr(args...)), VkResult>
    {
#if GLEEC_DEBUG
        VkResult res = ptr(std::forward<Args>(args)...);

        CHECK_VK(res);

        return res;
#else
        return ptr(std::forward<Args>(args)...);
#endif
    }
}

#define CALL_INSTANCE_PROC(instance, fun, ...)\
    ::GLEEC::Internal::Graphics::vk::callProcAddress(#fun,\
        reinterpret_cast<decltype(&fun)>(vkGetInstanceProcAddr(instance, #fun)),\
        __VA_ARGS__)
#define CALL_DEVICE_PROC(device, fun, ...)\
    ::GLEEC::Internal::Graphics::vk::callProcAddress(#fun,\
        reinterpret_cast<decltype(&fun)>(vkGetDeviceProcAddr(device, #fun)),\
        __VA_ARGS__)
