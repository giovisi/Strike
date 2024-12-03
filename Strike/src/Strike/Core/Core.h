#pragma once

#include <memory>

#ifdef STRK_ENABLE_ASSERTS
	#define STRK_ASSERT(x, ...) { if(!(x)) {STRK_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define STRK_CORE_ASSERT(x, ...) { if(!(x)) { STRK_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define STRK_ASSERT(x, ...)
	#define STRK_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define STRK_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Strike {
	template<typename T>
	using Scope = std::unique_ptr<T>;
	
	template<typename T>
	using Ref = std::shared_ptr<T>;
}