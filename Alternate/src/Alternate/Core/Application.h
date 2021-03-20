#pragma once

#include "Core.h"

#include "Window.h"
#include "LayerStack.h"
#include "Alternate/Events/Event.h"
#include "Alternate/Events/ApplicationEvent.h"

#include "Alternate/Core/Timestep.h"

#include "Alternate/ImGui/ImGuiLayer.h"

namespace Alternate 
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_instance;  }
		inline Window& GetWindow() { return *m_Window; }

	private:
		bool OnWindowClosed(WindowCloseEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
		bool OnWindowMinimized(WindowMinimizedEvent& e);
		bool OnWindowRestored(WindowRestoredEvent& e);
		
		void CloseWindow();

	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		uint32_t  m_LastFrameTime = 0;

	private:
		static Application* s_instance;
	};

	//To be defined in a CLIENT
	Application* CreateApplication();
}

