#pragma once

#include "PP/Platform.h"

#if PP_PLATFORM_WINDOWS
    #define GLEEC_WINDOWS 1
#elif PP_PLATFORM_MAC_OS
    #define GLEEC_MAC 1
#elif PP_PLATFORM_LINUX
    #define GLEEC_LINUX 1
#else
#error "Unknown platform for GLEEC!"
#endif
