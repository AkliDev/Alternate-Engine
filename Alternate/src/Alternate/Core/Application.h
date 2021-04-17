#pragma once

#include "Base.h"

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
		Application(const std::string& name);
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		

		void Close();

		static Application& Get() { return *s_instance; }
		inline Window& GetWindow() { return *m_Window; }
		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }	

	private:
		bool OnWindowClosed(WindowCloseEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
		bool OnWindowMinimized(WindowMinimizedEvent& e);
		bool OnWindowRestored(WindowRestoredEvent& e);

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

