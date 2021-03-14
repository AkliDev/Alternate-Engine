#include <Alternate.h>

#include "Platfrom/OpenGL/OpenGLShader.h"

#include "imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Alternate::Layer
{
public:
	ExampleLayer()
		:Layer("Example"), m_Camara(-1.6f, 1.6f,-0.9f, 0.9f)
	{
		CreateExampleRenderData();
	}

	void OnUpdate(Alternate::Timestep ts) override
	{
		//ALT_INFO("Delta time: {0}s ({1}ms)", ts.GetSeconds(), ts.GetMilliseconds());
		if (Alternate::Input::IsKeyPressed(ALT_KEY_W)) { m_CameraPostion.y += m_CameraMoveSpeed * ts; }
		if (Alternate::Input::IsKeyPressed(ALT_KEY_S)) { m_CameraPostion.y -= m_CameraMoveSpeed * ts; }
		if (Alternate::Input::IsKeyPressed(ALT_KEY_A)) { m_CameraPostion.x -= m_CameraMoveSpeed * ts; }
		if (Alternate::Input::IsKeyPressed(ALT_KEY_D)) { m_CameraPostion.x += m_CameraMoveSpeed * ts; }

		if (Alternate::Input::IsKeyPressed(ALT_KEY_1)) { m_CameraRotation += m_CameraRotationSpeed * ts; }
		if (Alternate::Input::IsKeyPressed(ALT_KEY_3)) { m_CameraRotation -= m_CameraRotationSpeed * ts; }

		if (Alternate::Input::IsKeyPressed(ALT_KEY_Q)) { m_CameraZoom += m_CameraZoomSpeed * ts; }
		if (Alternate::Input::IsKeyPressed(ALT_KEY_E)) { m_CameraZoom -= m_CameraZoomSpeed * ts; }
		if (m_CameraZoom < 0.01f) { m_CameraZoom = 0.01f; }

		Alternate::RenderCommand::SetClearColor({ 0.1, 0.1, 0.1, 1 });
		Alternate::RenderCommand::Clear();

		m_Camara.SetPosition(m_CameraPostion);
		m_Camara.SetRotation(m_CameraRotation);
		m_Camara.SetZoom(m_CameraZoom);

		Alternate::Renderer::BeginScene(m_Camara);

		static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(.1f));

		m_FlatColorShader->Bind();
		std::dynamic_pointer_cast<Alternate::OpenGLShader>(m_FlatColorShader) -> UploadUniformFloat3("u_Color", m_SquareColor);

		for ( int x = 0; x < 20; x++)
		{
			for (int y = 0; y < 20; y++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Alternate::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}
		
		m_TextureShader->Bind();
		m_CheckerBoardTexture->Bind(0);
		Alternate::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		m_TransparantTexture->Bind(0);
		Alternate::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		//triangle
		//Alternate::Renderer::Submit(m_Shader, m_VertexArray);

		Alternate::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Alternate::Event& event) override
	{
	}

private:
	void CreateExampleRenderData()
	{
		m_VertexArray.reset(Alternate::VertexArray::Create());

		float vertices[3 * 7] =
		{
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			 0.0f,  0.35f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f
		};

		Alternate::Ref<Alternate::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Alternate::VertexBuffer::Create(vertices, sizeof(vertices)));
		Alternate::BufferLayout layout =
		{
			{ Alternate::ShaderDataType::FLoat3, "a_Position" },
			{ Alternate::ShaderDataType::FLoat4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		Alternate::Ref<Alternate::IndexBuffer> indexBuffer;
		indexBuffer.reset(Alternate::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Alternate::VertexArray::Create());

		float squarVertices[5 * 4] =
		{
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Alternate::Ref<Alternate::VertexBuffer> squarVB;
		squarVB.reset(Alternate::VertexBuffer::Create(squarVertices, sizeof(squarVertices)));
		squarVB->SetLayout({ 
			{ Alternate::ShaderDataType::FLoat3, "a_Position" },
			{ Alternate::ShaderDataType::FLoat2, "a_TexCoord" },
		});
		m_SquareVA->AddVertexBuffer(squarVB);

		uint32_t squarIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Alternate::Ref<Alternate::IndexBuffer> squarIB;
		squarIB.reset(Alternate::IndexBuffer::Create(squarIndices, sizeof(squarIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squarIB);

		std::string vertexSrc = R"(
			#version 330 core
			layout (location = 0) in vec3 a_Position;
			layout (location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			  
			out vec4 v_VertexColor; // specify a color output to the fragment shader
			
			void main()
			{
			    gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0); 
			    v_VertexColor = a_Color; 
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			out vec4 FragColor;
			  
			in vec4 v_VertexColor; // the input variable from the vertex shader (same name and same type)  
			
			void main()
			{
			    FragColor = v_VertexColor * 0.5 + 0.5;
			} 
		)";

		std::string flatColorVertexSrc = R"(
			#version 330 core
			layout (location = 0) in vec3 a_Position; 
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			  
			out vec4 vertexColor; // specify a color output to the fragment shader
			
			void main()
			{
			    gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0); 
			}
		)";

		std::string flatColorFragmentSrc = R"(
			#version 330 core
			out vec4 FragColor;

			uniform vec3 u_Color;

			void main()
			{
			    FragColor = vec4(u_Color,1);
			} 
		)";
	
		m_Shader.reset(Alternate::Shader::Create(vertexSrc, fragmentSrc));
		m_FlatColorShader.reset(Alternate::Shader::Create(flatColorVertexSrc, flatColorFragmentSrc));
		m_TextureShader.reset(Alternate::Shader::Create("assets/shaders/Texture.glsl"));

		m_CheckerBoardTexture = Alternate::Texture2D::Create("assets/textures/Test.png");
		m_TransparantTexture = Alternate::Texture2D::Create("assets/textures/Goombah.png");

		m_TextureShader->Bind();
		std::dynamic_pointer_cast<Alternate::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
	}

	Alternate::Ref<Alternate::VertexArray> m_VertexArray;
	Alternate::Ref<Alternate::VertexArray> m_SquareVA;

	Alternate::Ref<Alternate::Shader> m_Shader;
	Alternate::Ref<Alternate::Shader> m_FlatColorShader;
	Alternate::Ref<Alternate::Shader> m_TextureShader;

	Alternate::Ref<Alternate::Texture2D> m_CheckerBoardTexture;
	Alternate::Ref<Alternate::Texture2D> m_TransparantTexture;

	Alternate::OrthographicCamera m_Camara;
	glm::vec3 m_CameraPostion = { 0.0f,0.0f,0.0f };
	float m_CameraRotation = 0.0f;
	float m_CameraZoom = 1.0f;

	float m_CameraMoveSpeed = 5.0f;
	float m_CameraRotationSpeed = 180.0f;
	float m_CameraZoomSpeed = 2.0f;

	glm::vec3 m_SquareColor = {0.2f, 0.3f, 0.8f};
};

class Sandbox : public Alternate::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Alternate::Application* Alternate::CreateApplication()
{
	return new Sandbox();
}