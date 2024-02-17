#pragma once

#if defined(_DEBUG) || defined(__DEBUG__) || defined(DEBUG)
    #define PP_BUILD_DEBUG 1
#endif

#if !defined(PP_BUILD_DEBUG) && (defined(NDEBUG) || defined(__OPTIMIZE))
    #define PP_BUILD_RELEASE 1
#endif

#if defined(PP_BUILD_DEBUG) && (defined(NDEBUG) || defined(__OPTIMIZE))
#error "Debug and Release both defined, check project config!"
#endif
