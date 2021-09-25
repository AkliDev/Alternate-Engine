
#include "EditorLayer.h"

#include <imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Alternate/Scene/SceneSerializer.h"

#include "Alternate/Utils/PlatformUtils.h"

namespace Alternate
{
	EditorLayer::EditorLayer()
		:Layer("EditorLayer"), m_CameraController(1280.0f / 720.0f, true)
	{
	}

	void EditorLayer::OnAttach()
	{
		ALT_PROFILE_FUNCTION();

		FramebufferSpecification fbSpec;
		fbSpec.Width = 1280;
		fbSpec.Height = 720;
		m_Framebuffer = FrameBuffer::Create(fbSpec);

		m_CheckerBoardTexture = Texture2D::Create("assets/textures/Test.png");
		m_TransparantTexture = Texture2D::Create("assets/textures/Goombah.png");

		m_CameraController.SetZoomLevel(1.0f);

		m_ActiveScene = CreateRef<Scene>();

#if 1
		//Entity
		m_SquareEntity = m_ActiveScene->CreateEntity("Square");
		m_SquareEntity.AddComponent<SpriteRendererComponent>(glm::vec4{ 0, 1, 0, 1 });

		m_CameraEntity = m_ActiveScene->CreateEntity("Camera A");
		m_CameraEntity.AddComponent<CameraComponent>().Camera.SetProjectionType(SceneCamera::ProjectionType::Perspective);
		m_CameraEntity.GetComponent<TransformComponent>().Translation.z = 30;

		m_SecondCamera = m_ActiveScene->CreateEntity("Camera B");
		auto& cc = m_SecondCamera.AddComponent<CameraComponent>();
		cc.Primary = false;

		class CameraController : public ScriptableEntity
		{
		public:
			void OnCreate()
			{

			}

			void OnDestroy()
			{

			}

			void OnUpdate(Timestep ts)
			{
				auto& translation = GetComponent<TransformComponent>().Translation;
				float speed = 5.0f;

				if (Input::IsKeyPressed(Key::ALT_KEY_W)) { translation.y += speed * ts; }
				if (Input::IsKeyPressed(Key::ALT_KEY_S)) { translation.y -= speed * ts; }
				if (Input::IsKeyPressed(Key::ALT_KEY_A)) { translation.x -= speed * ts; }
				if (Input::IsKeyPressed(Key::ALT_KEY_D)) { translation.x += speed * ts; }
			}
		};

		m_CameraEntity.AddComponent<NativeScriptComponent>().Bind<CameraController>();
#endif
		m_SceneHierarchyPanel.SetContex(m_ActiveScene);

		SceneSerializer serializer(m_ActiveScene);
	}

	void EditorLayer::OnDetach()
	{
		ALT_PROFILE_FUNCTION();
	}

	void EditorLayer::OnUpdate(Timestep ts)
	{
		ALT_PROFILE_FUNCTION();

		// Resize
		if (FramebufferSpecification spec = m_Framebuffer->GetSpecification();
			m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f && // zero sized framebuffer is invalid
			(spec.Width != m_ViewportSize.x || spec.Height != m_ViewportSize.y))
		{
			m_Framebuffer->Resize((int32_t)m_ViewportSize.x, (int32_t)m_ViewportSize.y);
			m_CameraController.OnResize((int32_t)m_ViewportSize.x, (int32_t)m_ViewportSize.y);
			m_ActiveScene->OnViewportResize((int32_t)m_ViewportSize.x, (int32_t)m_ViewportSize.y);
		}


		if (m_ViewportFocussed)
		{
			m_CameraController.OnUpdate(ts);
		}

		Renderer2D::ResetStats();
		m_Framebuffer->Bind();
		RenderCommand::SetClearColor({ 0.1, 0.1, 0.1, 1 });
		RenderCommand::Clear();

#if 0
		{
			static float wave = 0.5f;

			Alternate::Renderer2D::BeginScene(m_CameraEntity.GetComponent<CameraComponent>().Camera, m_CameraEntity.GetComponent<TransformComponent>().GetTransform());
			for (float y = -5.0f; y < 5.0f; y += 0.5f)
			{
				for (float x = -5.0f; x < 5.0f; x += 0.5f)
				{
					glm::vec4 color = { (x + 5.0f) / 10, 0.4f, (y + 5.0f) / 10, 0.75f };
					Alternate::Renderer2D::DrawQuad({ x, y , 5.0f - wave * y + wave * x }, { 0.45f, 0.45f }, color);
				}
			}
			Alternate::Renderer2D::EndScene();

			static float rotation = 0.0f;
			//rotation += ts * 100.0f;
			ALT_PROFILE_SCOPE("Render Draw");
			Alternate::Renderer2D::BeginScene(m_CameraEntity.GetComponent<CameraComponent>().Camera, m_CameraEntity.GetComponent<TransformComponent>().GetTransform());
			//Alternate::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_CheckerBoardTexture, 10.0f);
			Alternate::Renderer2D::DrawRotatedQuad({ 0.0f, -2.0f , 7.0f }, { 1.0f, 1.5f }, glm::radians(45.0f), m_Square2Color);
			Alternate::Renderer2D::DrawRotatedQuad({ 0.0f, 0.0f , 7.0f }, { 2.0f, 0.5f }, glm::radians(20.0f), m_SquareColor);
			Alternate::Renderer2D::DrawRotatedQuad({ 2.0f, 2.5f, 10.0f }, { 3.0f, 3.0f }, glm::radians(rotation), m_TransparantTexture);
			Alternate::Renderer2D::DrawRotatedQuad({ -2.0f, 2.5f , 10.0f }, { 3.0f, 3.0f }, glm::radians(-rotation), m_TransparantTexture);
			Alternate::Renderer2D::EndScene();
		}
#endif
		//update scene
		m_ActiveScene->OnUpdate(ts);

		//Renderer2D::EndScene();

		m_Framebuffer->Unbind();
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
				// Disabling full screen would allow the window to be moved to the front of other windows,
				// which we can't undo at the moment without finer window depth/z control.
				if (ImGui::MenuItem("New", "Ctr+N"))
				{
					NewScene();
				}

				if (ImGui::MenuItem("Open...", "Ctr+O"))
				{
					OpenScene();
				}

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

		m_SceneHierarchyPanel.OnImGuiRender();

		ImGui::Begin("Stats");
		auto stats = Renderer2D::GetStats();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quad Count: %d", stats.QuadCount);
		ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
		ImGui::Begin("Viewport");

		m_ViewportFocussed = ImGui::IsWindowFocused();
		m_ViewportHovered = ImGui::IsWindowHovered();

		Application::Get().GetImGuiLayer()->SetBlockEvents(!m_ViewportFocussed || !m_ViewportHovered);

		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();

		m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };

		uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
		ImGui::Image((void*)textureID, ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
		ImGui::End();
		ImGui::PopStyleVar();

		ImGui::End();
	}

	void EditorLayer::OnEvent(Event& e)
	{
		m_CameraController.OnEvent(e);

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<KeyPressedEvent>(ALT_BIND_EVENT_FN(EditorLayer::OnKeyPressed));
	}

	bool EditorLayer::OnKeyPressed(KeyPressedEvent& e)
	{
		//Shortcuts
		if (e.GetRepeatCount() > 0)
		{
			return false;
		}

		
		bool control = Input::IsKeyPressed(Key::ALT_KEY_LCTRL) || Input::IsKeyPressed(Key::ALT_KEY_RCTRL);
		bool shift = Input::IsKeyPressed(Key::ALT_KEY_LSHIFT) || Input::IsKeyPressed(Key::ALT_KEY_RSHIFT);
		switch (e.GetKeyCode())
		{
			case Key::ALT_KEY_N:
			{
				if (control)
				{
					NewScene();
				}
				break;
			}
			case Key::ALT_KEY_O:
			{
				if (control)
				{
					OpenScene();
				}
				break;
			}
			case Key::ALT_KEY_S:
			{
				if (control && shift)
				{
					SaveSceneAs();
				}
				break;
			}
		}
	}

	void EditorLayer::NewScene()
	{
		m_ActiveScene = CreateRef<Scene>();
		m_ActiveScene->OnViewportResize((int32_t)m_ViewportSize.x, (int32_t)m_ViewportSize.y);
		m_SceneHierarchyPanel.SetContex(m_ActiveScene);
	}

	void EditorLayer::OpenScene()
	{
		std::string filepath = FileDialogs::OpenFile("Alternate Scene (*.alt)\0*.alt\0");
		if (!filepath.empty())
		{
			m_ActiveScene = CreateRef<Scene>();
			m_ActiveScene->OnViewportResize((int32_t)m_ViewportSize.x, (int32_t)m_ViewportSize.y);
			m_SceneHierarchyPanel.SetContex(m_ActiveScene);

			SceneSerializer serializer(m_ActiveScene);
			serializer.Deserialize(filepath);
		}
	}

	void EditorLayer::SaveSceneAs()
	{
		std::string filepath = FileDialogs::SaveFile("Alternate Scene (*.alt)\0*.alt\0");
		if (!filepath.empty())
		{
			SceneSerializer serializer(m_ActiveScene);
			serializer.Serialize(filepath);
		}
	}
}