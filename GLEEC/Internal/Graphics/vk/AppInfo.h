#pragma once

#include "Config/Version.h"
#include "Internal/Graphics/Backends/vk.h"

#include <string_view>

namespace GLEEC::Internal::Graphics::vk
{
    struct AppInfo
    {
        VkApplicationInfo appInfo = {};

        explicit AppInfo(std::string_view name)
            : appInfo {
                VK_STRUCTURE_TYPE_APPLICATION_INFO,
                nullptr,
                name.data(),
                VK_MAKE_API_VERSION(0, GLEEC_VERSION_MAJOR, GLEEC_VERSION_MINOR, GLEEC_VERSION_PATCH),
                "GLEEC",
                VK_MAKE_API_VERSION(0, GLEEC_VERSION_MAJOR, GLEEC_VERSION_MINOR, GLEEC_VERSION_PATCH),
                VK_API_VERSION_1_3,
            }
        {
        }

        AppInfo()
            : AppInfo("GLEEC program")
        {
        }

        operator VkApplicationInfo() const
        {
            return appInfo;
        }
    };
}
