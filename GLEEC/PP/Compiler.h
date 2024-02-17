#pragma once

#if defined(__GNUC__) && !defined(__clang__)
    #define PP_COMPILER_GCC 1
#endif

#if defined(__clang__) && !defined(__GNUC__)
    #define PP_COMPILER_CLANG 1
#endif

#if defined(_MSC_VER)
    #define PP_COMPILER_MSVC 1
#endif

#if defined(__INTEL_LLVM_COMPILER)
	#if defined(SYCL_LANGUAGE_VERSION)	
		#define PP_COMPILER_INTELDPC 1
	#else
		#define PP_COMPILER_INTEL 1
	#endif
#endif

#if defined(__INTEL_COMPILER) && defined(__INTEL_COMPILER_BUILD_DATE)
	#define PP_COMPILER_INTEL_CLASSIC 1
#endif
