#pragma once

#include <cstdint>

#if INTPTR_MAX == INT64_MAX
    #define PP_ARCHITECTURE_64 1
#elif INTPTR_MAX == INT32_MAX
    #define PP_ARCHITECTURE_32 1
#elif INTPTR_MAX == INT16_MAX
    #define PP_ARCHITECTURE_16 1
#elif INTPTR_MAX == INT8_MAX
    #define PP_ARCHITECTURE_8 1
#endif

// whether or not to check if the architecture size is too small
#define PP_INTERNAL_ERROR_SMALL 1

#if PP_INTERNAL_ERROR_SMALL
    #if (INTPTR_MAX == PP_ARCHITECTURE_16) || (INTPTR_MAX == PP_ARCHITECTURE_8)
        #error "The current architecture size is too small for GLEEC!"
    #endif
#endif
