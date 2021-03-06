#include <Alternate.h>

#include "Alternate/Renderer/Renderer.h"
#include "Alternate/Renderer/Shader.h"
#include "Alternate/Renderer/VertexArray.h"
#include "Alternate/Renderer/Buffer.h"

class ExampleLayer : public Alternate::Layer
{
public:
	ExampleLayer()
		:Layer("Example")
	{
		CreateExampleRenderData();
	}

	void OnUpdate() override
	{
		//ALT_INFO("ExampleLayer::Update");

		Alternate::RenderCommand::SetClearColor({ 0.1, 0.1, 0.1, 1 });
		Alternate::RenderCommand::Clear();

		Alternate::Renderer::BeginScene();

		m_BlueShader->Bind();
		Alternate::Renderer::Submit(m_SquareVA);

		m_Shader->Bind();
		Alternate::Renderer::Submit(m_VertexArray);

		Alternate::Renderer::EndScene();
	}

	void OnEvent(Alternate::Event& event) override
	{
		//ALT_TRACE("{0}", event);
	}
private:

	void CreateExampleRenderData()
	{
		m_VertexArray.reset(Alternate::VertexArray::Create());

		float vertices[3 * 7] =
		{
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			 0.0f,  0.5f, 0.0f,	0.0f, 1.0f, 0.0f, 1.0f
		};

		std::shared_ptr<Alternate::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Alternate::VertexBuffer::Create(vertices, sizeof(vertices)));
		Alternate::BufferLayout layout =
		{
			{ Alternate::ShaderDataType::FLoat3, "a_Pos" },
			{ Alternate::ShaderDataType::FLoat4, "a_Col" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Alternate::IndexBuffer> indexBuffer;
		indexBuffer.reset(Alternate::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Alternate::VertexArray::Create());

		float squarVertices[3 * 4] =
		{
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<Alternate::VertexBuffer> squarVB;
		squarVB.reset(Alternate::VertexBuffer::Create(squarVertices, sizeof(squarVertices)));
		squarVB->SetLayout({ { Alternate::ShaderDataType::FLoat3, "a_Pos" } });
		m_SquareVA->AddVertexBuffer(squarVB);

		uint32_t squarIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Alternate::IndexBuffer> squarIB;
		squarIB.reset(Alternate::IndexBuffer::Create(squarIndices, sizeof(squarIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squarIB);

		std::string vertexSrc = R"(
			#version 330 core
			layout (location = 0) in vec3 aPos; // the position variable has attribute position 0
			layout (location = 1) in vec4 aCol;
			  
			out vec4 vertexColor; // specify a color output to the fragment shader
			
			void main()
			{
			    gl_Position = vec4(aPos, 1.0); // see how we directly give a vec3 to vec4's constructor
			    vertexColor = aCol; // set the output variable to a dark-red color
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			out vec4 FragColor;
			  
			in vec4 vertexColor; // the input variable from the vertex shader (same name and same type)  
			
			void main()
			{
			    FragColor = vertexColor * 0.5 + 0.5;
			} 
		)";

		std::string vertexSrc2 = R"(
			#version 330 core
			layout (location = 0) in vec3 aPos; // the position variable has attribute position 0
			  
			out vec4 vertexColor; // specify a color output to the fragment shader
			
			void main()
			{
			    gl_Position = vec4(aPos, 1.0); // see how we directly give a vec3 to vec4's constructor
			}
		)";

		std::string fragmentSrc2 = R"(
			#version 330 core
			out vec4 FragColor;
			  		
			void main()
			{
			    FragColor = vec4(0,0,1,1) * 0.5 + 0.5;
			} 
		)";

		m_Shader.reset(new Alternate::Shader(vertexSrc, fragmentSrc));
		m_BlueShader.reset(new Alternate::Shader(vertexSrc2, fragmentSrc2));
	}

	std::shared_ptr<Alternate::Shader> m_Shader;
	std::shared_ptr<Alternate::VertexArray> m_VertexArray;

	std::shared_ptr<Alternate::Shader> m_BlueShader;
	std::shared_ptr<Alternate::VertexArray> m_SquareVA;
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