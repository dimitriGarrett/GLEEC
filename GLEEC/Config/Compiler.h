#pragma once

#include "PP/Compiler.h"

#if PP_COMPILER_GCC
    #define GLEEC_GCC 1
#elif PP_COMPILER_CLANG
    #define GLEEC_CLANG 1
#elif PP_COMPILER_MSVC
    #define GLEEC_MSVC 1
#else
#error "Unsupported compiler for GLEEC!"
#endif
