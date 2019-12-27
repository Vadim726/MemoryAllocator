////////////////////////////////////////////////////////////////////////////
//	Created 	: 05.12.2019
//	Author		: Vadim Stydnansky
//	Copyright (c) 2019 the GameRay project.
////////////////////////////////////////////////////////////////////////////

#ifndef GAMERAY_BUILDING_H_
#define GAMERAY_BUILDING_H_

#ifndef _PLATFORM_
#	ifdef _WIN32
#		ifdef _WIN64
#			define PLATFORM64
#		else
#			define PLATFORM32
#		endif
#	elif defined(__linux__)
#		ifdef __x86_64__
#			define PLATFORM64
#		else
#			define PLATFORM32
#		endif
#	else
#		error Platform not supported
#	endif
#endif

#if !defined(STATIC_PLUGINS)
#	if defined(_WIN32)
#		define GAMERAY_ALIGN(alignment)     __declspec(align(alignment))
#		define GAMERAY_DLL_EXPORT           __declspec(dllexport)
#		define GAMERAY_DLL_IMPORT           __declspec(dllimport)
#			if (_MSC_VER)
#				pragma warning(disable : 4251)
#			endif
#	else
#		define GAMERAY_ALIGN(alignment)     __attribute__((aligned(alignment)))
#		define GAMERAY_DLL_EXPORT           __attribute__((__visibility__("default")))
#		define GAMERAY_DLL_IMPORT           __attribute__((__visibility__("default")))
#	endif
#else
#	define GAMERAY_DLL_EXPORT
#	define GAMERAY_DLL_IMPORT
#endif

#ifndef _ALWAYS_INLINE_
#   if defined(__GNUC__) && (__GNUC__ >= 4)
#      define ALWAYS_INLINE_				__attribute__((always_inline))	inline
#   elif defined(_MSC_VER)
#      define ALWAYS_INLINE					__forceinline
#   else
#      define ALWAYS_INLINE					inline
#   endif
#endif

#ifndef _FORCE_INLINE_
#   define FORCE_INLINE						inline
#else
#   define FORCE_INLINE						GR_ALWAYS_INLINE_
#endif

#ifndef _GAMERAY_API_
#	ifdef STATIC_PLUGINS
#		define GAMERAY_CORE_API
#	else
#	   if GAMERAY_CORE_BUILDING
#         define GAMERAY_CORE_API		GAMERAY_DLL_EXPORT
#      else
#         define GAMERAY_CORE_API		GAMERAY_DLL_IMPORT
#      endif
#   endif
#endif

#ifndef _ASSERT_
	#ifdef GAMERAY_DEBUG
		#ifdef _WIN32
			#define GAMERAY_DEBUG_BREAK() __debugbreak()
		#else
			#define GAMERAY_DEBUG_BREAK()  raise(SIGTRAP) 
		#endif
		#define GR_ASSERT(x) do { const volatile bool gameray_assert_b____ = !(x); if(gameray_assert_b____) GAMERAY_DEBUG_BREAK(); } while (false)
	#else
		#ifdef _WIN32		
			#define GR_ASSERT(x) __assume(x)
		#else
			#define GR_ASSERT(x) { false ? (void)(x) : (void)0; }
		#endif
	#endif
#endif

typedef char*					PSTR;
typedef const char*				PCSTR;

typedef unsigned char*			PBYTE;
typedef unsigned const char*	PCBYTE;

typedef void*					PVOID;
typedef const void*				PCVOID;

#include <thread>

#if (_WIN32) && (_MSC_VER)
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <signal.h>

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

namespace GameRay
{
	namespace Platform
	{
#pragma pack(push, 8)
		typedef struct tagTHREADNAME_INFO
		{
			DWORD dwType;	 // Must be 0x1000.
			LPCSTR szName;	// Pointer to name (in user addr space).
			DWORD dwThreadID; // Thread ID (-1=caller thread).
			DWORD dwFlags;	// Reserved for future use, must be zero.
		} THREADNAME_INFO;
#pragma pack(pop)

		inline void set_thread_name(DWORD dwThreadID, PCSTR threadName)
		{
			THREADNAME_INFO info;
			info.dwType = 0x1000;
			info.szName = threadName;
			info.dwThreadID = dwThreadID;
			info.dwFlags = 0;

			static const DWORD MS_VC_EXCEPTION = 0x406D1388;

			// Push an exception handler to ignore all following exceptions
#pragma warning(push)
#pragma warning(disable : 6320 6322)
			__try
			{
				RaiseException(MS_VC_EXCEPTION, 0, sizeof(info) / sizeof(ULONG_PTR), (ULONG_PTR*)& info);
			}
			__except (EXCEPTION_EXECUTE_HANDLER)
			{
			}
#pragma warning(pop)
		}

		inline void set_thread_name(std::thread& thread, PCSTR threadName)
		{
			DWORD threadId = ::GetThreadId(reinterpret_cast<HANDLE>(thread.native_handle()));
			set_thread_name(threadId, threadName);
		}
	}
}

#else

namespace GameRay
{
	namespace Platform
	{
		inline void set_thread_name(std::thread& thread, const char* threadName)
		{
			pthread_setname_np(thread.native_handle(), threadName);
		}
	}
}

#endif

#endif
