#pragma once

#include <memory.h>

#include "Core.h"
#include "spdlog/spdlog.h"

namespace Alternate
{
	class ALTERNATE_API Log
	{
	public: 
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

//Core log macros
#define ALT_CORE_TRACE(...)	::Alternate::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ALT_CORE_WARN(...)	::Alternate::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ALT_CORE_INFO(...)	::Alternate::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ALT_CORE_ERROR(...)	::Alternate::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ALT_CORE_FATEL(...)	::Alternate::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//Client log macros
#define ALT_TRACE(...)		::Alternate::Log::GetClientLogger()->trace(__VA_ARGS__)
#define ALT_WARN(...)		::Alternate::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ALT_INFO(...)		::Alternate::Log::GetClientLogger()->info(__VA_ARGS__)
#define ALT_ERROR(...)		::Alternate::Log::GetClientLogger()->error(__VA_ARGS__)
#define ALT_FATEL(...)		::Alternate::Log::GetClientLogger()->fatal(__VA_ARGS__)