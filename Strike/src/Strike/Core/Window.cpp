#include "strkpch.h"
#include "Window.h"

#ifdef STRK_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsWindow.h"
#endif

namespace Strike {
	Scope<Window> Window::Create(const WindowProps& props) {
#ifdef STRK_PLATFORM_WINDOWS
		return CreateScope<WindowsWindow>(props);
#else
		STRK_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
#endif
	}
}