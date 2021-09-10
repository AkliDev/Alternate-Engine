#pragma once

#include "Alternate.h"
#include "Panels/SceneHierarchyPanel.h"

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
		bool m_ViewportFocussed = false, m_ViewportHovered = false;
		OrthographicCameraController m_CameraController;

		Ref<VertexArray> m_SquareVA;
		Ref<Shader> m_FlatColorShader;
		Ref<Shader> m_PaletteShader;
		Ref<FrameBuffer> m_Framebuffer;

		Ref<Scene> m_ActiveScene;
		Entity m_SquareEntity;
		Entity m_CameraEntity;
		Entity m_SecondCamera;

		glm::vec2 m_ViewportSize = {0.0f, 0.0f};

		glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
		glm::vec4 m_Square2Color = { 0.8f, 0.3f, 0.2f, 1.0f };

		//Ref<Texture2D> m_CheckerBoardTexture;
		//Ref<Texture2D> m_TransparantTexture;
		Ref<Texture2D> m_WolfTexture;
		Ref<Texture2D> m_PaletteTexture;

		//Panels
		SceneHierarchyPanel m_SceneHierarchyPanel;
	};
}