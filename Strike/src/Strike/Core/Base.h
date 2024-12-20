#pragma once

#include <memory>

#ifdef STRK_DEBUG
	#if defined(STRK_PLATFORM_WINDOWS)
		#define STRK_DEBUGBREAK() __debugbreak()
	#else
		#error "Platform does not support debugbreak yet!"
	#endif
	#define STRK_ENABLE_ASSERTS
#else
	#define STRK_DEBUGBREAK()
#endif

#ifdef STRK_ENABLE_ASSERTS
	#define STRK_ASSERT(x, ...) { if(!(x)) {STRK_ERROR("Assertion Failed: {0}", __VA_ARGS__); STRK_DEBUGBREAK(); } }
	#define STRK_CORE_ASSERT(x, ...) { if(!(x)) { STRK_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); STRK_DEBUGBREAK(); } }
#else
	#define STRK_ASSERT(x, ...)
	#define STRK_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define STRK_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Strike {
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args) {
		return std::make_unique<T>(std::forward<Args>(args)...);
	}
	
	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args) {
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}