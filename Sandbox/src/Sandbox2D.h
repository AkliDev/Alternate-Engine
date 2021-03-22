#pragma once

#include "Alternate.h"

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
	Alternate::OrthographicCameraController m_CamaraController;

	Alternate::Ref<Alternate::VertexArray> m_SquareVA;
	Alternate::Ref<Alternate::Shader> m_FlatColorShader;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

	Alternate::Ref<Alternate::Texture2D> m_CheckerBoardTexture;
	Alternate::Ref<Alternate::Texture2D> m_TransparantTexture;
};