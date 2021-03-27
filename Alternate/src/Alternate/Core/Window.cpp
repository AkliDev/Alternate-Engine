#include "altpch.h"
#include "Window.h"

#ifdef ALT_PLATFORM_WINDOWS
#include "Platfrom/Windows/WindowsWindow.h"
#endif

namespace Alternate
{
	Scope<Window> Window::Create(const WindowProps& props)
	{
#ifdef ALT_PLATFORM_WINDOWS
		return CreateScope<WindowsWindow>(props);
#else
		ALT_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
#endif
	}

}