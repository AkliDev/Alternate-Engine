#pragma once

#include "Alternate.h"

#include "ParticleSystem.h"
#include "Alternate/Renderer/EditorCamera.h"

namespace Alternate
{
	class Sandbox2D : public Layer
	{
	public:
		Sandbox2D();
		virtual ~Sandbox2D() = default;

		void OnAttach() override;
		void OnDetach() override;

		void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender() override;
		void OnEvent(Event& e) override;
	private:
		bool OnKeyPressed(KeyPressedEvent& e);
		void SaveSceneAs();
	private:
		bool m_ViewportFocussed = false, m_ViewportHovered = false;
		OrthographicCameraController m_CameraController;

		Ref<VertexArray> m_SquareVA;
		Ref<Shader> m_FlatColorShader;
		Ref<FrameBuffer> m_Framebuffer;

		Entity m_HoveredEntity;

		ParticleSystem m_ParticleSystem;
		ParticleProps m_Particle;

		Ref<Scene> m_ActiveScene;

		uint32_t m_MapWidth, m_MapHeight;
		std::unordered_map<char, Alternate::Ref<Alternate::SubTexture2D>> s_TextureMap;

		EditorCamera m_EditorCamera;

		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
		glm::vec2 m_ViewportBounds[2];

		glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
		glm::vec4 m_Square2Color = { 0.8f, 0.3f, 0.2f, 1.0f };

		Ref<Texture2D> m_CheckerBoardTexture;
		Ref<Texture2D> m_TransparantTexture;
		Ref<Texture2D> m_SpriteSheet;
		Ref<SubTexture2D> m_TextureStairs, m_TextureBarrel, m_TextureTree;

		int m_GizmoType = -1;


	};
}
