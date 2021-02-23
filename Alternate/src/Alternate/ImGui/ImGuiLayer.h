#pragma once

#include "Alternate/Layer.h"

#include "Alternate/Events/KeyEvent.h"
#include "Alternate/Events/MouseEvent.h"
#include "Alternate/Events/ApplicationEvent.h"
namespace Alternate
{
	class ALTERNATE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		float m_Time = 0.0f;
	};
}