#pragma once

#include "Core.h"

#include "Window.h"
#include "LayerStack.h"
#include "Alternate/Events/Event.h"
#include "Alternate/Events/ApplicationEvent.h"



namespace Alternate 
{
	class ALTERNATE_API Application
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
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;

	private:
		static Application* s_instance;
	};

	//To be defined in a CLIENT
	Application* CreateApplication();
}

