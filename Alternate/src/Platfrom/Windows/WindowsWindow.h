#pragma once

#include "Alternate/Window.h"

#include <SDL.h>

namespace Alternate {

	class ALTERNATE_API WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		unsigned int GetWidth() const override { return m_Data.Width; }
		unsigned int GetHeight() const override { return m_Data.Height; }

		// Window attributes
		void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		virtual void* GetNativeWindow() const { return m_Window; }
		virtual SDL_GLContext& GetGLWindow() { return m_gl_context; }
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	private:
		SDL_Window* m_Window;
		SDL_GLContext m_gl_context;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;

		void HandleEvents();
	};

}

