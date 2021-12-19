#include "altpch.h"

#include "WindowsWindow.h"

#include "Alternate/Events/ApplicationEvent.h"
#include "Alternate/Events/KeyEvent.h"
#include "Alternate/Events/TextEvent.h"
#include "Alternate/Events/MouseEvent.h"

#include "Alternate/Renderer/Renderer.h"
#include "Alternate/Renderer/GraphicsContext.h"

namespace Alternate {

	static uint8_t s_SDLWindowCount = 0;

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		ALT_PROFILE_FUNCTION();

		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		ALT_PROFILE_FUNCTION();

		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		ALT_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (s_SDLWindowCount == 0)
		{
			ALT_PROFILE_SCOPE("SDL_Init");

			ALT_CORE_INFO("Initializing SDL");
			int success = SDL_Init(SDL_INIT_VIDEO);
			if (success != 0)
			{
				ALT_CORE_ASSERT(success, "Could not initialize SDL!");
			}
		}

		{
			ALT_PROFILE_SCOPE("SDLCreateWindow");
			m_Window = SDL_CreateWindow(props.Title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, props.Width, props.Height, SDL_WINDOW_OPENGL);
			SDL_SetWindowResizable(m_Window, SDL_TRUE);
			++s_SDLWindowCount;
		}

		m_Context = GraphicsContext::Create(m_Window);
		m_Context->Init();

		SDL_SetWindowData(m_Window, "data", &m_Data);
		SetVSync(false);
	}

	void WindowsWindow::Shutdown()
	{
		ALT_PROFILE_FUNCTION();

		m_Context->DeleteRenderContext();
		SDL_DestroyWindow(m_Window);
		s_SDLWindowCount--;

		if (s_SDLWindowCount == 0)
		{
			SDL_Quit();
		}
	}

	void WindowsWindow::OnUpdate()
	{
		ALT_PROFILE_FUNCTION();

		HandleEvents();
		m_Context->SwapBuffer();
	}

	void WindowsWindow::HandleEvents()
	{
		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_WINDOWEVENT:
			{
				if (event.window.windowID == SDL_GetWindowID(m_Window))
				{
					switch (event.window.event)
					{
					case SDL_WINDOWEVENT_SIZE_CHANGED:
					{
						int width = (int)event.window.data1;
						int height = (int)event.window.data2;

						WindowData& data = *(WindowData*)SDL_GetWindowData(m_Window, "data");
						data.Width = width;
						data.Height = height;

						WindowResizeEvent ALT_event(width, height);
						data.EventCallback(ALT_event);

						break;
					}
					case SDL_WINDOWEVENT_CLOSE:
					{
						WindowData& data = *(WindowData*)SDL_GetWindowData(m_Window, "data");
						WindowCloseEvent ALT_event;
						data.EventCallback(ALT_event);
						break;
					}
					case SDL_WINDOWEVENT_MINIMIZED:
					{
						WindowData& data = *(WindowData*)SDL_GetWindowData(m_Window, "data");
						WindowMinimizedEvent ALT_event;
						data.EventCallback(ALT_event);
						break;
					}
					case SDL_WINDOWEVENT_RESTORED:
					{
						WindowData& data = *(WindowData*)SDL_GetWindowData(m_Window, "data");
						WindowRestoredEvent ALT_event;
						data.EventCallback(ALT_event);
						break;
					}
					}
				}
				break;
			}
			case SDL_TEXTINPUT:
			{
				WindowData& data = *(WindowData*)SDL_GetWindowData(m_Window, "data");
				TextInputEvent ALT_event(event.text.text);
				data.EventCallback(ALT_event);
				break;
			}
			case SDL_KEYDOWN:
			{

				WindowData& data = *(WindowData*)SDL_GetWindowData(m_Window, "data");

				if (event.key.repeat != 0)
				{
					KeyPressedEvent ALT_event(event.key.keysym.scancode, event.key.repeat);
					data.EventCallback(ALT_event);
				}
				else
				{
					KeyPressedEvent ALT_event(event.key.keysym.scancode, 0);
					data.EventCallback(ALT_event);
				}

				KeyTypedEvent ALT_event(event.key.keysym.sym);
				data.EventCallback(ALT_event);
				break;
			}
			case SDL_KEYUP:
			{
				WindowData& data = *(WindowData*)SDL_GetWindowData(m_Window, "data");
				KeyReleasedEvent ALT_event(event.key.keysym.scancode);
				data.EventCallback(ALT_event);
				break;
			}
			case SDL_MOUSEBUTTONDOWN:
			{
				WindowData& data = *(WindowData*)SDL_GetWindowData(m_Window, "data");
				MouseButtonPressedEvent ALT_event(event.button.button);
				data.EventCallback(ALT_event);
				break;
			}
			case SDL_MOUSEBUTTONUP:
			{
				WindowData& data = *(WindowData*)SDL_GetWindowData(m_Window, "data");
				MouseButtonReleasedEvent ALT_event(event.button.button);
				data.EventCallback(ALT_event);
				break;
			}
			case SDL_MOUSEWHEEL:
			{
				WindowData& data = *(WindowData*)SDL_GetWindowData(m_Window, "data");
				MouseScrolledEvent ALT_event(float(event.wheel.x), float(event.wheel.y));
				data.EventCallback(ALT_event);
				break;
			}
			case SDL_MOUSEMOTION:
			{
				WindowData& data = *(WindowData*)SDL_GetWindowData(m_Window, "data");
				MouseMovedEvent ALT_event(float(event.motion.x), float(event.motion.y));
				data.EventCallback(ALT_event);
				break;
			}
			}
		}
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		ALT_PROFILE_FUNCTION();

		if (enabled)
			SDL_GL_SetSwapInterval(1);
		else
			SDL_GL_SetSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}
}
