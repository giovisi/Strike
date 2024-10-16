#pragma once

#ifdef STRK_PLATFORM_WINDOWS
	#ifdef STRK_BUILD_DLL
		#define STRIKE_API __declspec(dllexport)
	#else
		#define STRIKE_API __declspec(dllimport)
	#endif
#else
	#error Strike only supports Windows!
#endif

#ifdef STRK_ENABLE_ASSERTS
	#define STRK_ASSERT(x, ...) { if(!(x)) {STRK_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define STRK_CORE_ASSERT(x, ...) { if(!(x)) { STRK_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define STRK_ASSERT(x, ...)
	#define STRK_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)