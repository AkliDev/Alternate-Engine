#pragma once

#include "Alternate.h"

#include "ParticleSystem.h"

class Sandbox2D : public Alternate::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	void OnAttach() override;
	void OnDetach() override;

	void OnUpdate(Alternate::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Alternate::Event& e) override;
private:
	Alternate::OrthographicCameraController m_CameraController;

	Alternate::Ref<Alternate::VertexArray> m_SquareVA;
	Alternate::Ref<Alternate::Shader> m_FlatColorShader;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
	glm::vec4 m_Square2Color = { 0.8f, 0.3f, 0.2f, 1.0f };

	Alternate::Ref<Alternate::Texture2D> m_CheckerBoardTexture;
	Alternate::Ref<Alternate::Texture2D> m_TransparantTexture;
	Alternate::Ref<Alternate::Texture2D> m_SpriteSheet;
	Alternate::Ref<Alternate::SubTexture2D> m_TextureStairs, m_TextureBarrel, m_TextureTree;

	ParticleSystem m_ParticleSystem;
	ParticleProps m_Particle;

	uint32_t m_MapWidth, m_MapHeight;
	std::unordered_map<char, Alternate::Ref<Alternate::SubTexture2D>> s_TextureMap;
};