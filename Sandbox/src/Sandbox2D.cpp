#include "Sandbox2D.h"

#include "imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platfrom/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D()
	:Layer("Sandbox2D"), m_CamaraController(1280.0f / 720.0f, true)
{
}

void Sandbox2D::OnAttach()
{
	m_SquareVA = Alternate::VertexArray::Create();

	float squarVertices[3 * 4] =
	{
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	Alternate::Ref<Alternate::VertexBuffer> squarVB;
	squarVB.reset(Alternate::VertexBuffer::Create(squarVertices, sizeof(squarVertices)));
	squarVB->SetLayout({
		{ Alternate::ShaderDataType::FLoat3, "a_Position" }
		});
	m_SquareVA->AddVertexBuffer(squarVB);

	uint32_t squarIndices[6] = { 0, 1, 2, 2, 3, 0 };
	Alternate::Ref<Alternate::IndexBuffer> squarIB;
	squarIB.reset(Alternate::IndexBuffer::Create(squarIndices, sizeof(squarIndices) / sizeof(uint32_t)));
	m_SquareVA->SetIndexBuffer(squarIB);

	m_FlatColorShader = Alternate::Shader::Create("assets/shaders/FlatColor.glsl");
}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate(Alternate::Timestep ts)
{

	m_CamaraController.OnUpdate(ts);

	//Alternate::RenderCommand::SetClearColor({ 0.1, 0.1, 0.1, 1 });
	//Alternate::RenderCommand::Clear();

	Alternate::Renderer::BeginScene(m_CamaraController.GetCamera());

	m_FlatColorShader->Bind();
	std::dynamic_pointer_cast<Alternate::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);

	Alternate::Renderer::Submit(m_FlatColorShader, m_SquareVA, glm::translate(glm::mat4(1.0f), glm::vec3(-1,-1,0)));

	Alternate::Renderer::EndScene();
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
