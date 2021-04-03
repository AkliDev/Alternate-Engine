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
	ALT_PROFILE_FUNCTION();
	m_CheckerBoardTexture = Alternate::Texture2D::Create("assets/textures/Test.png");
	m_TransparantTexture = Alternate::Texture2D::Create("assets/textures/Goombah.png");
}

void Sandbox2D::OnDetach()
{
	ALT_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(Alternate::Timestep ts)
{
	ALT_PROFILE_FUNCTION();

	m_CamaraController.OnUpdate(ts);
	
	{
		ALT_PROFILE_SCOPE("Render Prep");
		Alternate::RenderCommand::SetClearColor({ 0.1, 0.1, 0.1, 1 });
		Alternate::RenderCommand::Clear();
	}

	{
		ALT_PROFILE_SCOPE("Render Draw");
		Alternate::Renderer2D::BeginScene(m_CamaraController.GetCamera());
		Alternate::Renderer2D::DrawQuad({ 1.0f, 1.0f }, { 1.0f, 1.0f }, m_SquareColor);
		Alternate::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, m_Square2Color);
		Alternate::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	ALT_PROFILE_FUNCTION();

	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color2D", glm::value_ptr(m_SquareColor));
	ImGui::ColorEdit4("Square2 Color2D", glm::value_ptr(m_Square2Color));
	ImGui::End();
}

void Sandbox2D::OnEvent(Alternate::Event& e)
{
	m_CamaraController.OnEvent(e);
}
