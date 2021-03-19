#include "altpch.h"
#include "OrthographicCameraController.h"

#include "Alternate/Input.h"
#include "Alternate/KeyCodes.h"
namespace Alternate
{
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		:m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio* m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation)
	{

	}

	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
		m_CameraTranslationSpeed = m_ZoomLevel;
		if (Input::IsKeyPressed(ALT_KEY_W)) { m_CameraPostion.y += m_CameraTranslationSpeed * ts; }
		if (Input::IsKeyPressed(ALT_KEY_S)) { m_CameraPostion.y -= m_CameraTranslationSpeed * ts; }
		if (Input::IsKeyPressed(ALT_KEY_A)) { m_CameraPostion.x -= m_CameraTranslationSpeed * ts; }
		if (Input::IsKeyPressed(ALT_KEY_D)) { m_CameraPostion.x += m_CameraTranslationSpeed * ts; }

		if (m_Rotation == true)
		{
			if (Input::IsKeyPressed(ALT_KEY_Q)) { m_CameraRotation += m_CameraRotationSpeed * ts; }
			if (Input::IsKeyPressed(ALT_KEY_E)) { m_CameraRotation -= m_CameraRotationSpeed * ts; }
			m_Camera.SetRotation(m_CameraRotation);
		}

		m_Camera.SetPosition(m_CameraPostion);	
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<MouseScrolledEvent>(ALT_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrollEvent));
		dispatcher.Dispatch<WindowResizeEvent>(ALT_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}

	bool OrthographicCameraController::OnMouseScrollEvent(MouseScrolledEvent& e)
	{
		m_ZoomLevel -= e.GetYOffset() * 0.1f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

}