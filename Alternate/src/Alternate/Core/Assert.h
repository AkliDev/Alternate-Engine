#pragma once

#include "Alternate/Core/Base.h"
#include "Alternate/Core/Log.h"
#include <filesystem>

#ifdef ALT_ENABLE_ASSERTS
	// Alternatively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
	// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
	#define ALT_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { ALT##type##ERROR(msg, __VA_ARGS__); ALT_DEBUGBREAK(); } }
	#define ALT_INTERNAL_ASSERT_WITH_MSG(type, check, ...) ALT_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
	#define ALT_INTERNAL_ASSERT_NO_MSG(type, check) ALT_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", std::filesystem::path(__FILE__).filename().string(), __LINE__)
	
	#define ALT_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
	#define ALT_INTERNAL_ASSERT_GET_MACRO(...) ALT_EXPAND_MACRO( ALT_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, ALT_INTERNAL_ASSERT_WITH_MSG, ALT_INTERNAL_ASSERT_NO_MSG) )
	
	// Currently accepts at least the condition and one additional parameter (the message) being optional
	#define ALT_ASSERT(...) ALT_EXPAND_MACRO( ALT_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
	#define ALT_CORE_ASSERT(...) ALT_EXPAND_MACRO( ALT_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
	#define ALT_ASSERT(...)
	#define ALT_CORE_ASSERT(...)
#endif
