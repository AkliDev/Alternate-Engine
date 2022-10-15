#pragma once

#include "Alternate.h"
#include "Panels/SceneHierarchyPanel.h"
#include "Panels/ContentBrowserPanel.h"
#include "Alternate/Renderer/EditorCamera.h"

namespace Alternate
{
	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		void OnAttach() override;
		void OnDetach() override;

		void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender() override;
		void OnEvent(Event& e) override;
	private:
		bool OnKeyPressed(KeyPressedEvent& e);
		bool OnMouseButtonPressed(MouseButtonPressedEvent& e);
		
		void NewScene();
		void OpenScene();
		void SaveSceneAs();
	private:
		bool m_ViewportFocussed = false, m_ViewportHovered = false;
		OrthographicCameraController m_CameraController;

		Ref<VertexArray> m_SquareVA;
		Ref<Shader> m_FlatColorShader;
		Ref<FrameBuffer> m_Framebuffer;

		Entity m_HoveredEntity;

		Ref<Scene> m_ActiveScene;

		EditorCamera m_EditorCamera;

		glm::vec2 m_ViewportSize = {0.0f, 0.0f};
		glm::vec2 m_ViewportBounds[2];

		glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
		glm::vec4 m_Square2Color = { 0.8f, 0.3f, 0.2f, 1.0f };

		Ref<Texture2D> m_CheckerBoardTexture;
		Ref<Texture2D> m_TransparantTexture;
	
		int m_GizmoType = -1;

		//Panels
		SceneHierarchyPanel m_SceneHierarchyPanel;
		ContentBrowserPanel m_ContentBrowserPanel;
	};
}
