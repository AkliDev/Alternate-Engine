#pragma once
#include <memory>

#include "Alternate/Core/PlatformDetection.h"

#ifdef ALT_DEBUG
	#if defined(ALT_PLATFORM_WINDOWS)
		#define ALT_DEBUGBREAK() __debugbreak()
	#elif defined(ALT_PLATFORM_LINUX)
		#include <signal.h>
		#define ALT_DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif
	#define ALT_ENABLE_ASSERTS
#else
	#define ALT_DEBUGBREAK()
#endif

#define ALT_EXPAND_MACRO(x) x
#define ALT_STRINGIFY_MACRO(x) #x

#define BIT(x) (1 << x)

#define ALT_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace Alternate
{
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}

#include "Alternate/Core/Log.h"
#include "Alternate/Core/Assert.h"
