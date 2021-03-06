#include "altpch.h"
#include "Application.h"

#include "Alternate/Renderer/Renderer.h"

namespace Alternate
{
	Application* Application::s_instance = nullptr;

	Application::Application()
	{
		ALT_CORE_ASSERT(!s_instance, "Appliaction already exisits!");
		s_instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(ALT_BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		m_VertexArray.reset(VertexArray::Create());

		float vertices[3 * 7] =
		{
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			 0.0f,  0.5f, 0.0f,	0.0f, 1.0f, 0.0f, 1.0f
		};

		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		BufferLayout layout =
		{
			{ ShaderDataType::FLoat3, "a_Pos" },
			{ ShaderDataType::FLoat4, "a_Col" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(VertexArray::Create());

		float squarVertices[3 * 4] =
		{
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<VertexBuffer> squarVB;
		squarVB.reset(VertexBuffer::Create(squarVertices, sizeof(squarVertices)));
		squarVB->SetLayout({{ ShaderDataType::FLoat3, "a_Pos" }});						
		m_SquareVA->AddVertexBuffer(squarVB);

		uint32_t squarIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<IndexBuffer> squarIB;
		squarIB.reset(IndexBuffer::Create(squarIndices, sizeof(squarIndices) / sizeof(uint32_t)));
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

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
		m_BlueShader.reset(new Shader(vertexSrc2, fragmentSrc2));
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (m_Running)
		{
			RenderCommand::SetClearColor({ 0.1, 0.1, 0.1, 1 });
			RenderCommand::Clear();

			Renderer::BeginScene();

			m_BlueShader->Bind();
			Renderer::Submit(m_SquareVA);

			m_Shader->Bind();
			Renderer::Submit(m_VertexArray);

			Renderer::EndScene();

			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate();
			}

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
			{
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(ALT_BIND_EVENT_FN(Application::OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);

			if (e.Handled)
			{
				break;
			}
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}