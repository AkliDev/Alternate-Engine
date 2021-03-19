#include "altpch.h"
#include "Application.h"

#include "Alternate/Renderer/Renderer.h"
#include "Alternate/KeyCodes.h"

#include <SDL.h>

namespace Alternate
{
	Application* Application::s_instance = nullptr;

	Application::Application()
	{
		ALT_CORE_ASSERT(!s_instance, "Appliaction already exisits!");
		s_instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(ALT_BIND_EVENT_FN(Application::OnEvent));
		m_Window->SetVSync(false);

		Renderer::Init();
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (m_Running)
		{
			
			uint32_t  time = SDL_GetTicks(); // TODO make platform independent 
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_Minimized)
			{
				for (Layer* layer : m_LayerStack) { layer->OnUpdate(timestep); }			
			}

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack) { layer->OnImGuiRender(); }
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(ALT_BIND_EVENT_FN(Application::OnWindowClosed));
		dispatcher.Dispatch<KeyPressedEvent>(ALT_BIND_EVENT_FN(Application::OnKeyPressedEvent));
		dispatcher.Dispatch<WindowResizeEvent>(ALT_BIND_EVENT_FN(Application::OnWindowResized));
		dispatcher.Dispatch<WindowMinimizedEvent>(ALT_BIND_EVENT_FN(Application::OnWindowMinimized));
		dispatcher.Dispatch<WindowRestoredEvent>(ALT_BIND_EVENT_FN(Application::OnWindowRestored));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);

			if (e.Handled)
			{
				break;
			}
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	bool Application::OnWindowClosed(WindowCloseEvent& e)
	{
		CloseWindow();
		return true;
	}

	bool Application::OnKeyPressedEvent(KeyPressedEvent& e)
	{
		if (e.GetKeyCode() == ALT_KEY_ESCAPE) { CloseWindow(); }
		return true;
	}

	bool Application::OnWindowResized(WindowResizeEvent& e)
	{
		Renderer::OnWindowResized(e.GetWidth(), e.GetHeight());
		return false;
	}

	bool Application::OnWindowMinimized(WindowMinimizedEvent& e)
	{
		m_Minimized = true;
		return false;
	}

	bool Application::OnWindowRestored(WindowRestoredEvent& e)
	{
		m_Minimized = false;
		return false;
	}

	void Application::CloseWindow()
	{
		m_Running = false;
	}

}