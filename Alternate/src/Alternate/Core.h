#pragma once

#ifdef ALT_PLATFORM_WINDOWS
	#ifdef ALT_BUILD_DLL
		#define ALTERNATE_API _declspec(dllexport)
	#else
		#define ALTERNATE_API _declspec(dllimport)
	#endif
#else
	#error Alternate only supports Windows!
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