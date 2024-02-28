#pragma once

#include "Internal/Log/Log.h"
#include "CHECK_VK.h"

namespace GLEEC::Internal::Graphics::vk
{
    // this just makes it so i can log if the call instance proc
    // is nullptr for whatever reason
    template <typename T>
    bool check_p(std::string_view name, T* ptr)
    {
#if GLEEC_DEBUG
        if (ptr) return true;

        LOG_WARNING("Vulkan: failed to call InstanceProcAddress func: {}, it was nullptr!", name);

        return false;
#else
        return ptr;
#endif
    }
}

#define CALL_INSTANCE_PROC(instance, func, ...) if (auto p = reinterpret_cast<decltype(&func)>(vkGetInstanceProcAddr(instance, #func)); ::GLEEC::Internal::Graphics::vk::check_p(#func, p)) p(__VA_ARGS__)

#define CHECK_CALL_INSTANCE_PROC(instance, func, ...) if (auto p = reinterpret_cast<decltype(&func)>(vkGetInstanceProcAddr(instance, #func)); ::GLEEC::Internal::Graphics::vk::check_p(#func, p)) CHECK_VK(p(__VA_ARGS__))
