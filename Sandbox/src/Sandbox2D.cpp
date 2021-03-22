#include "Sandbox2D.h"

#include <imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	:Layer("Sandbox2D"), m_CamaraController(1280.0f / 720.0f, true)
{
}

void Sandbox2D::OnAttach()
{
	m_CheckerBoardTexture = Alternate::Texture2D::Create("assets/textures/Test.png");
	m_TransparantTexture = Alternate::Texture2D::Create("assets/textures/Goombah.png");
}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate(Alternate::Timestep ts)
{

	m_CamaraController.OnUpdate(ts);

	Alternate::RenderCommand::SetClearColor({ 0.1, 0.1, 0.1, 1 });
	Alternate::RenderCommand::Clear();

	Alternate::Renderer2D::BeginScene(m_CamaraController.GetCamera());

	Alternate::Renderer2D::DrawQuad({ 1.0f, 1.0f }, 0, { 1.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f });
	Alternate::Renderer2D::DrawQuad({ 0.0f, 0.0f }, 0, { 1.0f, 1.0f }, m_TransparantTexture);
	Alternate::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, 0, { 10.0f, 10.0f }, m_CheckerBoardTexture);	
	
	Alternate::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color2D", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Alternate::Event& e)
{
	m_CamaraController.OnEvent(e);
}
