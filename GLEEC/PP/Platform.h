#pragma once

#if defined(_AIX)
	#define PP_PLATFORM_AIX 1

	#if defined(_AIX43)
		#define PP_AIX_VERSION_43 1
	#elif defined(_AIX41)
		#define PP_AIX_VERSION_41 1
	#elif defined(_AIX32)
		#define PP_AIX_VERSION_32 1
	#endif
#endif

#if defined(__ANDROID__)
	#include <android/api-level.h>

	#define PP_PLATFORM_ANDROID 1

	#if __ANDROID_API__ == 1
		#define PP_ANDROID_VERSION_10 1
	#elif __ANDROID_API__ == 2
		#define PP_ANDROID_VERSION_11 1
	#elif __ANDROID_API__ == 3
		#define PP_ANDROID_VERSION_15 1
	#elif __ANDROID_API__ == 4
		#define PP_ANDROID_VERSION_16 1
	#elif __ANDROID_API__ == 5
		#define PP_ANDROID_VERISON_20 1
	#elif __ANDROID_API__ == 6
		#define PP_ANDROID_VERSION_201 1
	#elif __ANDROID_API__ == 7
		#define PP_ANDROID_VERSION_21 1
	#elif __ANDROID_API__ == 8
		#define PP_ANDROID_VERSION_22 1
	#elif __ANDROID_API__ == 9
		#define PP_ANDROID_VERSION_23 1
	#elif __ANDROID_API__ == 10
		#define PP_ANDROID_VERSION_233 1
	#elif __ANDROID_API__ == 11
		#define PP_ANDROID_VERSION20 1
	#endif
#endif

// yes this business went out of business, it's just here for completeness sake
#if defined(UTS)
	#define PP_PLATFORM_AMDAHL_UTS 1
#endif

#if defined(AMIGA)
	#define PP_PLATFORM_AMIGA 1
#endif

#if defined(aegis)
	#define PP_PLATFORM_APOLLO_AEGIS 1
#endif

#if defined(apollo)
	#define PP_PLATFORM_APOLLO_DOMAIN 1
#endif

#if defined(__BEOS__)
	#define PP_PLATFORM_BEOS 1
#endif

#if defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__DragonFly__)
	#define PP_PLATFORM_BSD 1
#endif

#if defined(__DragonFly__)
	#define PP_PLATFORM_DRAGONFLY 1
#endif

#if !defined(PLATFORM_BSD) && defined(__bsdi__)
	#define PP_PLATFORM_BSD_OS 1
#endif

#if defined(__convex__)
	#define PP_PLATFORM_CONVEX_OS 1
#endif

#if defined(__CYGWIN__)
	#define PP_PLATFORM_CYGWIN 1
#endif

#if defined(DGUX)
	#define PP_PLATFORM_DGUX 1
#endif

#if defined(_SEQUENT_) || defined(sequent)
	#define PP_PLATFORM_DYNIX 1
#endif

#if defined(__ECOS)
	#define PP_PLATFORM_ECOS 1
#endif

#if defined(__EMX__)
	#define PP_PLATFORM_EMX 1
#endif

#if defined(__FreeBSD__)
	#include <osreldate.h>

	#define PP_PLATFORM_FREEBSD 1

	#if __FreeBSD_version == 119411
		#define PP_FREEBSD_VERSION_20 1
	#elif __FreeBSD_version == 220000
		#define PP_FREEBSD_VERSION22 1
	#elif __FreeBSD_version == 300005
		#define PP_FREEBSD_VERSION30 1
	#elif __FreeBSD_version == 400017
		#define PP_FREEBSD_VERSION40 1
	#elif __FreeBSD_version == 450000
		#define PP_FREEBSD_VERSION45 1
	#endif
#endif

#if defined(__GNU__) || defined(__gnu_hurd__)
	#define PP_PLATFORM_GNU_HURD 1
#endif

#if defined(__FREEBSD_kernel) && defined(__GLIBC__)
	#define PP_PLATFORM_GNU_KFREEBSD 1
#endif

#if defined(__gnu_linux__)
	#define PP_PLATFORM_GNU_LINUX 1
#endif

#if defined (__hiuxmpp)
	#define PP_PLATFORM_HIUX_MPP 1
#endif

#if defined(_hpux) || defined(hpux) || defined(__hpux)
	#define PP_PLATFORM_HPUX 1
#endif

#if defined(__OS400__)
	#define PP_PLATFORM_IBM_OS400 1
#endif

#if defined(__INTEGRITY)
	#define PP_PLATFORM_INTEGRITY 1
#endif

#if defined(__INTERIX)
	#define PP_PLATFORM_INTERIX 1
#endif

#if defined(sgi) || defined(__sgi)
	#define PP_PLATFORM_IRIX 1
#endif

#if defined(__linux__) || defined(linux) || defined(__linux)
	#define PP_PLATFORM_LINUX 1
#endif

#if defined(__Lynx__)
	#define PP_PLATFORM_LYNX 1
#endif

#if defined(__APPLE__) && defined(__MACH__)
	#include <TargetConditionals.h>

	#define PP_PLATFORM_APPLE 1

	#if TARGET_IPHONE_SIMULATOR == 1
		#define PP_PLATFORM_IOS_SIMULATOR 1
	#elif TARGET_OS_IPHONE == 1
		#define PP_PLATFORM_IOS 1
	#elif TARGET_OS_MAC == 1
		#define PP_PLATFORM_MAC_OS 1
	#endif
#endif

#if defined(__OS9000) || defined(_OSK)
	#define PP_PLATFORM_MICROWARE_OS9 1
#endif

#if defined(__minix)
	#define PP_PLATFORM_MINIX 1
#endif

#if defined(__MORPHOS__)
	#define PP_PLATFORM_MORPHOS 1
#endif

#if defined(mpeix) || defined(__mpexl)
	#define PP_PLATFORM_MPE 1
#endif

#if defined(MSDOS) || defined(__MSDOS__) || defined(_MSDOS) || defined(__DOS__)
	#define PP_PLATFORM_MSDOS 1
#endif

#if defined(__TANDEM)
	#define PP_PLATFORM_NONSTOP 1
#endif

#if defined(__nucleus__)
	#define PP_PLATFORM_NUCLEUS 1
#endif

#if defined(OS2) || defined(_OS2) || defined(__OS2__) || defined(__TOS_OS2__)
	#define PP_PLATFORM_OS2 1
#endif

#if defined(__palmos__)
	#define PP_PLATFORM_PALM_OS 1
#endif

#if defined(EPLAN9)
	#define PP_PLATFORM_PLAN9 1
#endif

#if defined(pyr)
	#define PP_PLATFORM_PYRAMID 1
#endif

#if defined(__QNX__) || defined(__QNXNTO__)
	#define PP_PLATFORM_QNX 1
#endif

#if defined(sinux)
	#define PP_PLATFORM_RELIANT_UNIX 1
#endif

#if defined(M_I386) || defined(M_XENIX) || defined(_SCO_DS)
	#define PP_PLATFORM_SCO_OPENSERVER 1
#endif

#if defined(sun) || defined(__sun)
	#if defined(__SVR4 || defined(__svr4__))
		#define PP_PLATFORM_SOLARIS 1
	#else
		#define PP_PLATFORM_SUNOS 1
	#endif
#endif

#if defined(__VOS__)
	#define PP_PLATFORM_STRATUS_VOS 1
#endif

#if defined(__sysv__) || defined(__SVR4) || defined(__svr4__) || defined(_SYSTYPE_SVR4)
	#define PP_PLATFORM_SVR4_ENVIRONMENT 1
#endif

#if defined(__SYLLABLE__)
	#define PP_PLATFORM_SYLLABLE 1
#endif

#if defined(__SYMBIAN32__)
	#define PP_PLATFORM_SYMBIAN 1
#endif

#if defined(__osf__) || defined(__osf)
	#define PP_PLATFORM_TRU64 1
#endif

#if defined(ultrix) || defined(__ultrix) || defined(__ultrix__) || (defined(unix) && defined(vax))
	#define PP_PLATFORM_ULTRIX 1
#endif

#if defined(_UNICOS)
	#define PP_PLATFORM_UNICOS 1
#endif

#if defined(_CRAY) || defined(__crayx1)
	#define PP_PLATFORM_UNICOS_MP 1
#endif

#if defined(__unix__) || defined(__unix)
	#define PP_PLATFORM_UNIX 1
#endif

#if defined(sco) || defined(_UNIXWARE7)
	#define PP_PLATFORM_UNIXWARE 1
#endif

#if defined(_UWIN)
	#define PP_PLATFORM_U_WIN 1
#endif

#if defined(VMS) || defined(__VMS)
	#define PP_PLATFORM_VMS 1
#endif

#if defined(__VXWORKS__) || defined(__vxworks)
	#define PP_PLATFORM_VXWORKS 1

	#if defined(__RTP__)
		#define PP_VXWORKS_REALTIME 1
	#elif defined(_WRS_KERNEL)
		#define PP_VXWORKS_KERNEL 1
	#endif
#endif

#if defined(_WIN16) || defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__)
	#define PP_PLATFORM_WINDOWS 1

	#if defined(_WIN64)
		#define PP_WINDOWS_64 1
	#elif defined(_WIN32)
		#define PP_WINDOWS_32 1
	#elif defined(_WIN16)
		#define PP_WINDOWS_16 1
	#endif
#endif

#if defined(_WIN32_WCE)
	#define PP_PLATFORM_WINCE 1
#endif

#if defined(_WINDU_SOURCE)
	#define PP_PLATFORM_WINDU 1
#endif

#if defined(__MVS__) || defined(__HOS_MVS__) || defined(__TOS_MVS__)
	#define PP_PLATFORM_ZOS 1

	#if defined(__HOS_MVS__)
		#define PP_ZOS_HOST 1
	#elif defined(__TOS_MVS__)
		#define PP_ZOS_TARGET 1
	#endif
#endif
