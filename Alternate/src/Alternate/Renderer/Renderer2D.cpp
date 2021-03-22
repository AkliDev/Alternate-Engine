#include "altpch.h"
#include "Renderer2D.h"

#include "Alternate/Renderer/RenderCommand.h"
#include "Alternate/Renderer/VertexArray.h"
#include "Alternate/Renderer/Shader.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Alternate
{
	struct Renderer2DStorage
	{
		Ref<VertexArray> QuadVertexArray;
		Ref<Shader> TextureShader;
		Ref<Texture2D> WhiteTexture;
	};

	static Renderer2DStorage* s_Data;

	void Renderer2D::Init()
	{
		s_Data = new Renderer2DStorage();

		s_Data->QuadVertexArray = VertexArray::Create();

		float squarVertices[5 * 4] =
		{
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Ref<VertexBuffer> squarVB;
		squarVB.reset(VertexBuffer::Create(squarVertices, sizeof(squarVertices)));
		squarVB->SetLayout({
			{ ShaderDataType::FLoat3, "a_Position" },
			{ ShaderDataType::FLoat2, "a_TexCoord" },
			});
		s_Data->QuadVertexArray->AddVertexBuffer(squarVB);

		uint32_t squarIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Ref<IndexBuffer> squarIB;
		squarIB.reset(IndexBuffer::Create(squarIndices, sizeof(squarIndices) / sizeof(uint32_t)));
		s_Data->QuadVertexArray->SetIndexBuffer(squarIB);

		s_Data->WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_Data->WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		s_Data->TextureShader = Shader::Create("assets/shaders/Texture.glsl");
		s_Data->TextureShader->Bind();
		s_Data->TextureShader->SetInt("u_Texture", 0);
	}

	void Renderer2D::ShutDown()
	{
		delete s_Data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		s_Data->TextureShader->Bind();
		s_Data->TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	}

	void Renderer2D::EndScene()
	{

	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const float rotation, const glm::vec2& scale, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, rotation, scale, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const float rotation, const glm::vec2& scale, const glm::vec4& color)
	{
		s_Data->WhiteTexture->Bind();

		s_Data->TextureShader->SetFloat4("u_Color", color);
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0, 0, 1)) * glm::scale(glm::mat4(1.0f), { scale.x, scale.y, 1.0f });
		s_Data->TextureShader->SetMat4("u_Transform", transform);

		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const float rotation, const glm::vec2& scale, const Ref<Texture2D>& texture)
	{
		DrawQuad({ position.x, position.y, 0.0f }, rotation, scale, texture);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const float rotation, const glm::vec2& scale, const Ref<Texture2D>& texture)
	{
		texture->Bind();

		s_Data->TextureShader->SetFloat4("u_Color", glm::vec4(1.0f));
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0, 0, 1)) * glm::scale(glm::mat4(1.0f), { scale.x, scale.y, 1.0f });
		s_Data->TextureShader->SetMat4("u_Transform", transform);

		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}
}