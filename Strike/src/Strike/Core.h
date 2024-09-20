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