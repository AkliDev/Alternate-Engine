
#include "EditorLayer.h"

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

namespace Alternate
{
	EditorLayer::EditorLayer()
		:Layer("EditorLayer"), m_CameraController(1280.0f / 720.0f, true)
	{
	}

	void EditorLayer::OnAttach()
	{
		ALT_PROFILE_FUNCTION();

		Alternate::FrameBufferSpecification fbSpec;
		fbSpec.Width = 1280;
		fbSpec.Height = 720;
		m_FrameBuffer = Alternate::FrameBuffer::Create(fbSpec);

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

		m_CameraController.SetZoomLevel(5.0f);
	}

	void EditorLayer::OnDetach()
	{
		ALT_PROFILE_FUNCTION();
	}

	void EditorLayer::OnUpdate(Alternate::Timestep ts)
	{
		ALT_PROFILE_FUNCTION();

		if (m_ViewportFocussed)
		{
			m_CameraController.OnUpdate(ts);
		}

		Alternate::Renderer2D::ResetStats();
		{
			ALT_PROFILE_SCOPE("Render Prep");
			m_FrameBuffer->Bind();
			Alternate::RenderCommand::SetClearColor({ 0.1, 0.1, 0.1, 1 });
			Alternate::RenderCommand::Clear();
		}

#if 1
		{
			static float rotation = 0.0f;
			rotation += ts * 500.0f;
			ALT_PROFILE_SCOPE("Render Draw");
			Alternate::Renderer2D::BeginScene(m_CameraController.GetCamera());
			Alternate::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_CheckerBoardTexture, 10.0f);
			Alternate::Renderer2D::DrawRotatedQuad({ 0.0f, -2.0f , 0.15f }, { 1.0f, 1.5f }, glm::radians(45.0f), m_Square2Color);
			Alternate::Renderer2D::DrawRotatedQuad({ 0.0f, 0.0f , 0.15f }, { 2.0f, 0.5f }, glm::radians(20.0f), m_SquareColor);
			// quad with other shader
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
		m_FrameBuffer->Unbind();
	}

	void EditorLayer::OnImGuiRender()
	{
		ALT_PROFILE_FUNCTION();

		static bool dockspaceOpen = true;
		static bool opt_fullscreen = true;
		static bool opt_padding = false;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			const ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->WorkPos);
			ImGui::SetNextWindowSize(viewport->WorkSize);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}
		else
		{
			dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
		// and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		if (!opt_padding)
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
		if (!opt_padding)
			ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				// Disabling fullscreen would allow the window to be moved to the front of other windows,
				// which we can't undo at the moment without finer window depth/z control.
				ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
				ImGui::MenuItem("Padding", NULL, &opt_padding);
				ImGui::Separator();

				if (ImGui::MenuItem("Exit")) Alternate::Application::Get().Close();
				ImGui::Separator();

				if (ImGui::MenuItem("Close", NULL, false))
					dockspaceOpen = false;
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

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

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
		ImGui::Begin("Viewport");

		m_ViewportFocussed = ImGui::IsWindowFocused();
		m_ViewportHovered = ImGui::IsWindowHovered();
		
		Application::Get().GetImGuiLayer()->SetBlockEvents(!m_ViewportFocussed || !m_ViewportHovered);
		
		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		if (m_ViewPortSize != *((glm::vec2*)&viewportPanelSize) && viewportPanelSize.x > 0 && viewportPanelSize.y > 0)
		{
			m_FrameBuffer->Resize((uint32_t)viewportPanelSize.x, (uint32_t)viewportPanelSize.y);
			m_ViewPortSize = { viewportPanelSize.x, viewportPanelSize.y };

			m_CameraController.OnResize(viewportPanelSize.x, viewportPanelSize.y);
		}
		uint32_t textureID = m_FrameBuffer->GetColorAttachmentRendererID();
		ImGui::Image((void*)textureID, ImVec2{ m_ViewPortSize.x, m_ViewPortSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
		ImGui::End();
		ImGui::PopStyleVar();

		ImGui::End();
	}

	void EditorLayer::OnEvent(Alternate::Event& e)
	{
		m_CameraController.OnEvent(e);
	}
}