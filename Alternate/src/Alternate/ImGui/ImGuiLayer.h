#pragma once

#include "Alternate/Core/Layer.h"

#include "Alternate/Events/TextEvent.h"
#include "Alternate/Events/KeyEvent.h"
#include "Alternate/Events/MouseEvent.h"
#include "Alternate/Events/ApplicationEvent.h"
namespace Alternate
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& e) override;
		void OnImGuiRender() override;

		void Begin();
		void End();

		void SetBlockEvents(bool block) { m_BlockEvents = block; };

		void SetDarkThemeColors();
	private:
		bool OnTextInputEvent(TextInputEvent& e);

		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);

		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);

		bool OnWindowResizeEvent(WindowResizeEvent& e);

	private:
		bool m_BlockEvents = true;
		float m_Time = 0.0f;
	};
}