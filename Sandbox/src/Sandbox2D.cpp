#include "Sandbox2D.h"

#include <imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Alternate/Scene/SceneSerializer.h"

#include "Alternate/Utils/PlatformUtils.h"

#include "ImGuizmo.h"

#include "Alternate/Math/Math.h"

namespace Alternate
{
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

		FramebufferSpecification fbSpec;
		fbSpec.Attachments = { FramebufferTextureFormat::RGBA8, FramebufferTextureFormat::RED_INTEGER, FramebufferTextureFormat::Depth };
		fbSpec.Width = 1280;
		fbSpec.Height = 720;
		m_Framebuffer = FrameBuffer::Create(fbSpec);

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

		m_CameraController.SetZoomLevel(1.0f);

		m_EditorCamera = EditorCamera(30.0f, 1.778f, 0.1f, 1000.0f);
	}

	void Sandbox2D::OnDetach()
	{
		ALT_PROFILE_FUNCTION();
	}

	void Sandbox2D::OnUpdate(Alternate::Timestep ts)
	{
		ALT_PROFILE_FUNCTION();

		// Resize
		if (FramebufferSpecification spec = m_Framebuffer->GetSpecification();
			m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f && // zero sized framebuffer is invalid
			(spec.Width != m_ViewportSize.x || spec.Height != m_ViewportSize.y))
		{
			m_Framebuffer->Resize((int32_t)m_ViewportSize.x, (int32_t)m_ViewportSize.y);
			m_CameraController.OnResize(m_ViewportSize.x, m_ViewportSize.y);
			m_EditorCamera.SetViewportSize(m_ViewportSize.x, m_ViewportSize.y);
		}

		if (m_ViewportFocussed)
		{
			m_CameraController.OnUpdate(ts);
		}
		m_EditorCamera.OnUpdate(ts);

		Renderer2D::ResetStats();
		m_Framebuffer->Bind();
		RenderCommand::SetClearColor({ 0.1, 0.1, 0.1, 1 });
		RenderCommand::Clear();

		//Clear entity ID attachment to -1
		m_Framebuffer->ClearAttachment(1, -1);

		Renderer2D::BeginScene(m_EditorCamera);

		Renderer2D::DrawQuad({ 2.0f, 0.0f,-1.0f }, { 2.0f, 2.0f }, m_CheckerBoardTexture);

		Renderer2D::EndScene();

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
			glm::vec2 mousePos = Alternate::Input::GetMousePosition();
			auto x = mousePos.x;
			auto y = mousePos.y;
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

		Renderer2D::BeginScene(m_EditorCamera);

		Renderer2D::DrawQuad({ 1.0f, 0.0f, 1.0f }, { 2.0f, 2.0f }, m_TransparantTexture);

		Renderer2D::EndScene();

		m_Framebuffer->Unbind();
	}

	void Sandbox2D::OnImGuiRender()
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
		ImGuiStyle& style = ImGui::GetStyle();
		float minWindSizeX = style.WindowMinSize.x;
		style.WindowMinSize.x = 370.0f;
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		style.WindowMinSize.x = minWindSizeX;

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Save As...", "Ctr+Shift+S"))
				{
					SaveSceneAs();
				}

				if (ImGui::MenuItem("Exit")) Application::Get().Close();
				ImGui::Separator();

				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		ImGui::Begin("Stats");

		std::string name = "None";
		if (m_HoveredEntity) name = m_HoveredEntity.GetComponent<TagComponent>().Tag;
		ImGui::Text("Hovered Entity: %s", name.c_str());

		auto stats = Renderer2D::GetStats();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quad Count: %d", stats.QuadCount);
		ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
		ImGui::Begin("Viewport");
		auto viewportMinRegion = ImGui::GetWindowContentRegionMin();
		auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();
		auto viewportOffset = ImGui::GetWindowPos();
		m_ViewportBounds[0] = { viewportMinRegion.x + viewportOffset.x, viewportMinRegion.y + viewportOffset.y };
		m_ViewportBounds[1] = { viewportMaxRegion.x + viewportOffset.x, viewportMaxRegion.y + viewportOffset.y };

		m_ViewportFocussed = ImGui::IsWindowFocused();
		m_ViewportHovered = ImGui::IsWindowHovered();
		Application::Get().GetImGuiLayer()->SetBlockEvents(!m_ViewportFocussed && !m_ViewportHovered);

		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };

		uint64_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
		ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

		ImGui::End();
		ImGui::PopStyleVar();

		ImGui::End();
	}

	void Sandbox2D::OnEvent(Event& e)
	{
		m_CameraController.OnEvent(e);
		m_EditorCamera.OnEvent(e);

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<KeyPressedEvent>(ALT_BIND_EVENT_FN(Sandbox2D::OnKeyPressed));
	}

	bool Sandbox2D::OnKeyPressed(KeyPressedEvent& e)
	{
		//Shortcuts
		if (e.GetRepeatCount() > 0)
		{
			return false;
		}

		bool control = Input::IsKeyPressed(Key::KEY_LCTRL) || Input::IsKeyPressed(Key::KEY_RCTRL);
		bool shift = Input::IsKeyPressed(Key::KEY_LSHIFT) || Input::IsKeyPressed(Key::KEY_RSHIFT);
		switch (e.GetKeyCode())
		{
		case Key::KEY_S:
		{
			if (control && shift)
			{
				SaveSceneAs();
			}
			break;
		}

		// Gizmos
		case Key::KEY_Q:
		{
			if (!ImGuizmo::IsUsing())
			{
				m_GizmoType = -1;
			}
			break;
		}
		case Key::KEY_W:
		{
			if (!ImGuizmo::IsUsing())
			{
				m_GizmoType = ImGuizmo::OPERATION::TRANSLATE;
			}
			break;
		}
		case Key::KEY_E:
		{
			if (!ImGuizmo::IsUsing())
			{
				m_GizmoType = ImGuizmo::OPERATION::ROTATE;
			}
			break;
		}
		case Key::KEY_R:
		{
			if (!ImGuizmo::IsUsing())
			{
				m_GizmoType = ImGuizmo::OPERATION::SCALE;
			}
			break;
		}
		}
	}

	void Sandbox2D::SaveSceneAs()
	{
		std::string filepath = FileDialogs::SaveFile("Alternate Scene (*.alt)\0*.alt\0");
		if (!filepath.empty())
		{
			SceneSerializer serializer(m_ActiveScene);
			serializer.Serialize(filepath);
		}
	}
}
