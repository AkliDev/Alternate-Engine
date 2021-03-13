#pragma once
#include <memory>

#ifdef ALT_PLATFORM_WINDOWS
#if ALT_DYNAMIC_LINK
	#ifdef ALT_BUILD_DLL
		#define ALTERNATE_API _declspec(dllexport)
	#else
		#define ALTERNATE_API _declspec(dllimport)
	#endif
#else
	#define ALTERNATE_API
#endif
#else
	#error Alternate only supports Windows!
#endif

#ifdef ALT_DEBUG
	#define ALT_ENABLE_ASSERTS
#endif

#ifdef ALT_ENABLE_ASSERTS
	#define ALT_ASSERT(x, ...) { if (!(x)) { ALT_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define ALT_CORE_ASSERT(x, ...) { if (!(x)) { ALT_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define ALT_ASSERT(x, ...)
	#define ALT_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define ALT_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Alternate
{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}