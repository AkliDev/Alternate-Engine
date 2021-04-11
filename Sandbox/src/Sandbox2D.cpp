#include "Sandbox2D.h"

#include <imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

static const uint32_t s_MathWidth = 20;
static const char* s_MapTiles =
"WDWWWWWWWWWWWWWWWWWW"
"WWWWWWWWWWWWWWWWWWWW"
"WWWWWWWWWWWWWWWWWWWW"
"WWWWWWWWWWWWWWWWWWWW"
"WWWWWWWWWWWWWWWWWWWW"
"WWWWWWWWWWWWWWWWWWWW"
"WWWWWWWWWWWWWWWWWWWW"
"WWWWWWWWWWWWWWWWWWWW"
"WWWWWWWWWWWWWWWWWWWW"
"WWWWWWWWWWWWWWWWWWWW"
"WWWWWWWWWWWWWWWWWWWW"
"WWWWWWWWWWWWWWWWWWWW"
"WWWWWWWWWWWWWWWWWWWW"
"WWWWWWWWWWWWWWWWWWWW"
"WWWWWWWWWWWWWWWWWWWW"
"WWWWWWWWWWWWWWWWWWWW"
"WWWWWWWWWWWAWWWWWWWW"
"WWWWWWWWWWWWWWWWWWWW"
"WWWWWWWWWWWWWWWWWWWW"
"WWWWWWWWWWWWWWWWWWWW"
;

Sandbox2D::Sandbox2D()
	:Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true)
{
}

void Sandbox2D::OnAttach()
{
	ALT_PROFILE_FUNCTION();

	m_CheckerBoardTexture = Alternate::Texture2D::Create("assets/textures/Test.png");
	m_TransparantTexture = Alternate::Texture2D::Create("assets/textures/Goombah.png");
	m_SpriteSheet = Alternate::Texture2D::Create("assets/game/textures/RPGpack_sheet_2X.png");

	m_TextureStairs = Alternate::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 7, 6 }, { 128, 128 });
	m_TextureBarrel = Alternate::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 9, 2 }, { 128, 128 });
	m_TextureTree = Alternate::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 4, 1 }, { 128, 128 }, { 1, 2 });

	m_MapWidth = s_MathWidth;
	m_MapHeight = uint32_t(strlen(s_MapTiles) / m_MapWidth);
	s_TextureMap['D'] = Alternate::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 6, 11 }, { 128, 128 });
	s_TextureMap['W'] = Alternate::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 11, 11 }, { 128, 128 });




	m_Particle.ColorBegin = { 0 / 255.0f, 127 / 255.0f, 255 / 255.0f, 1.0f };
	m_Particle.ColorEnd = { 142 / 255.0f, 182 / 255.0f, 255 / 255.0f, 1.0f };
	m_Particle.SizeBegin = 0.5f, m_Particle.SizeVariation = 0.3f, m_Particle.SizeEnd = 0.0f;
	m_Particle.LifeTime = 5.0f;
	m_Particle.Velocity = { 0.0f, 0.0f };
	m_Particle.VelocityVariation = { 3.0f, 1.0f };
	m_Particle.Position = { 0.0f, 0.0f };

	m_CameraController.SetZoomLevel(5.0f);
}

void Sandbox2D::OnDetach()
{
	ALT_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(Alternate::Timestep ts)
{
	ALT_PROFILE_FUNCTION();

	m_CameraController.OnUpdate(ts);

	Alternate::Renderer2D::ResetStats();
	{
		ALT_PROFILE_SCOPE("Render Prep");

		Alternate::RenderCommand::SetClearColor({ 0.1, 0.1, 0.1, 1 });
		Alternate::RenderCommand::Clear();
	}

#if 0
	{
		static float rotation = 0.0f;
		rotation += ts * 500.0f;
		ALT_PROFILE_SCOPE("Render Draw");
		Alternate::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Alternate::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_CheckerBoardTexture, 10.0f);
		Alternate::Renderer2D::DrawRotatedQuad({ 0.0f, -2.0f , 0.15f }, { 1.0f, 1.5f }, glm::radians(45.0f), m_Square2Color);
		Alternate::Renderer2D::DrawRotatedQuad({ 0.0f, 0.0f , 0.15f }, { 2.0f, 0.5f }, glm::radians(20.0f), m_SquareColor);
		Alternate::Renderer2D::DrawRotatedQuad({ 2.0f, 2.5f, 0.15f }, { 3.0f, 3.0f }, glm::radians(rotation), m_TransparantTexture);
		Alternate::Renderer2D::DrawRotatedQuad({ -2.0f, 2.5f , 0.15f }, { 3.0f, 3.0f }, glm::radians(-rotation), m_TransparantTexture);
		Alternate::Renderer2D::EndScene();

		Alternate::Renderer2D::BeginScene(m_CameraController.GetCamera());
		for (float y = -5.0f; y < 5.0f; y += 0.5f)
		{
			for (float x = -5.0f; x < 5.0f; x += 0.5f)
			{
				glm::vec4 color = { (x + 5.0f) / 10, 0.4f, (y + 5.0f) / 10, 0.75f };
				Alternate::Renderer2D::DrawQuad({ x, y , 0.1f }, { 0.45f, 0.45f }, color);
			}
		}
		Alternate::Renderer2D::EndScene();
	}
#endif
	if (Alternate::Input::IsMouseButtonPressed(1))
	{
		auto [x, y] = Alternate::Input::GetMousePosition();
		auto width = Alternate::Application::Get().GetWindow().GetWidth();
		auto height = Alternate::Application::Get().GetWindow().GetHeight();

		auto bounds = m_CameraController.GetBounds();
		auto pos = m_CameraController.GetCamera().GetPosition();
		x = (x / width) * bounds.GetWidth() - bounds.GetWidth() * 0.5f;
		y = bounds.GetHeight() * 0.5f - (y / height) * bounds.GetHeight();
		m_Particle.Position = { x + pos.x, y + pos.y };
		for (int i = 0; i < 5; i++)
			m_ParticleSystem.Emit(m_Particle);
	}

	m_ParticleSystem.OnUpdate(ts);
	m_ParticleSystem.OnRender(m_CameraController.GetCamera());

	Alternate::Renderer2D::BeginScene(m_CameraController.GetCamera());

	for (uint32_t y = 0; y < m_MapHeight; y++)
	{
		for (uint32_t x = 0; x < m_MapWidth; x++)
		{
			char tileType = s_MapTiles[x + y * m_MapWidth];
			Alternate::Ref<Alternate::SubTexture2D> texture;
			if (s_TextureMap.find(tileType) != s_TextureMap.end())
			{
				texture = s_TextureMap[tileType];
			}
			else
			{
				texture = m_TextureBarrel;
			}

			Alternate::Renderer2D::DrawQuad({ x - (m_MapWidth * 0.5f), m_MapHeight - y - (m_MapHeight * 0.5f) }, { 1.0f, 1.0f }, texture);
		}
	}

	//Alternate::Renderer2D::DrawQuad({ 0.0f, 0.0f}, { 1.0f, 1.0f }, m_TextureStairs);
	//Alternate::Renderer2D::DrawQuad({ 0.0f, 1.0f}, { 1.0f, 1.0f }, m_TextureBarrel);
	//Alternate::Renderer2D::DrawQuad({ 1.0f, 0.0f }, { 1.0f, 2.0f }, m_TextureTree);
	Alternate::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ALT_PROFILE_FUNCTION();

	ImGui::Begin("Settings");
	auto stats = Alternate::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quad Count: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

	ImGui::ColorEdit4("Square Color2D", glm::value_ptr(m_SquareColor));
	ImGui::ColorEdit4("Square2 Color2D", glm::value_ptr(m_Square2Color));
	ImGui::End();
}

void Sandbox2D::OnEvent(Alternate::Event& e)
{
	m_CameraController.OnEvent(e);
}