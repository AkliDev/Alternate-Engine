#include "altpch.h"

#include "WindowsWindow.h"

#include "Alternate/Events/ApplicationEvent.h"
#include "Alternate/Events/KeyEvent.h"
#include "Alternate/Events/MouseEvent.h"

#include <glad/glad.h>

namespace Alternate {

	static bool s_SDLInitialized = false;

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		ALT_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (s_SDLInitialized == 0)
		{
			int success = SDL_Init(SDL_INIT_VIDEO);
			if (success != 0)
			{
				ALT_CORE_ASSERT(success, "Could not initialize SDL!");
			}
			s_SDLInitialized = true;
		}
		SDL_GL_LoadLibrary(NULL); // Default OpenGL is fine.

		 // Request an OpenGL 4.6 context (should be core)
		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
		// Also request a depth buffer
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
		//enable debug context
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);

		m_Window = SDL_CreateWindow(props.Title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, props.Width, props.Height, SDL_WINDOW_OPENGL);
		SDL_SetWindowResizable(m_Window, SDL_TRUE);
		m_gl_context = SDL_GL_CreateContext(m_Window);
		SDL_GL_MakeCurrent(m_Window, m_gl_context);

		int status = gladLoadGLLoader(SDL_GL_GetProcAddress);
		ALT_CORE_ASSERT(status, "failed to initialize Glad!");

		SDL_SetWindowData(m_Window, "data", &m_Data);

		SetVSync(true);	
	}

	void WindowsWindow::Shutdown()
	{
		SDL_DestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate()
	{
		HandleEvents();
		SDL_GL_SwapWindow(m_Window);
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
					}
				}
				break;
			}
			case SDL_KEYDOWN:
			{
				WindowData& data = *(WindowData*)SDL_GetWindowData(m_Window, "data");
				if (event.key.repeat != 0)
				{
					KeyPressedEvent ALT_event(event.key.keysym.sym, event.key.repeat);
					data.EventCallback(ALT_event);
				}
				else
				{
					KeyPressedEvent ALT_event(event.key.keysym.sym, 0);
					data.EventCallback(ALT_event);
				}
				break;
			}
			case SDL_KEYUP:
			{
				WindowData& data = *(WindowData*)SDL_GetWindowData(m_Window, "data");
				KeyReleasedEvent ALT_event(event.key.keysym.sym);
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
