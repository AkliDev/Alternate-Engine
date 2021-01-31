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