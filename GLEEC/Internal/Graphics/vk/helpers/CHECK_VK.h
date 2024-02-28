#pragma once

#include "Internal/Log/Log.h"

#ifdef GLEEC_DEBUG
#define CHECK_VK(fun) if (fun != VK_SUCCESS) LOG_WARNING("Vulkan Error: Vulkan function: {} failed at line {}, in function {}, in file {}!", #fun, __LINE__, __func__, __FILE__)
#else
#define CHECK_VK(fun) fun
#endif
