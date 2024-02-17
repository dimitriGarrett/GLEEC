#pragma once

#include "Compiler.h"

#if PP_COMPILER_GCC || PP_COMPILER_CLANG
    #define PP_CURRENT_FUNCTION __PRETTY_FUNCTION__
#elif PP_COMPILER_MSVC
    #define PP_CURRENT_FUNCTION __FUNCSIG__
#else
    #define PP_CURRENT_FUNCTION __func__
#endif

#if PP_COMPILER_GCC || PP_COMPILER_CLANG
    #define PP_UNREACHABLE() (__builtin_unreachable())
#elif PP_COMPILER_MSVC
    #define PP_UNREACHABLE() (__assume(false))
#else // as suggested by: https://en.cppreference.com/w/c/program/unreachable
    [[noreturn]] inline void pp_unreachable_impl() {}
#define PP_UNREACHABLE() (pp_unreachable_impl())
#endif
