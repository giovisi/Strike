#pragma once

#include "Strike/Core/Base.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Strike {

	class  Log{
	public:
		static void Init();
		
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger;  }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger;  }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	};

}

// Core log macros

#define STRK_CORE_TRACE(...)   ::Strike::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define STRK_CORE_INFO(...)    ::Strike::Log::GetCoreLogger()->info(__VA_ARGS__)
#define STRK_CORE_WARN(...)    ::Strike::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define STRK_CORE_ERROR(...)   ::Strike::Log::GetCoreLogger()->error(__VA_ARGS__)
#define STRK_CORE_FATAL(...)   ::Strike::Log::GetCoreLogger()->fatal(__VA_ARGS__)


// Client log macros
#define STRK_TRACE(...)        ::Strike::Log::GetClientLogger()->trace(__VA_ARGS__)
#define STRK_INFO(...)         ::Strike::Log::GetClientLogger()->info(__VA_ARGS__)
#define STRK_WARN(...)         ::Strike::Log::GetClientLogger()->warn(__VA_ARGS__)
#define STRK_ERROR(...)        ::Strike::Log::GetClientLogger()->error(__VA_ARGS__)
#define STRK_FATAL(...)        ::Strike::Log::GetClientLogger()->fatal(__VA_ARGS__)
