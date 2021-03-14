#include "altpch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platfrom/OpenGL/OpenGLShader.h"
namespace Alternate
{
	Alternate::Shader* Shader::Create(const std::string& filePath)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:	ALT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!") return nullptr;
			case RendererAPI::API::OpenGL:	return new OpenGLShader(filePath);
		}

		ALT_CORE_ASSERT(false, "Unkown RendererAPI!")
		return nullptr;
	}

	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragemntSrc)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:	ALT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!") return nullptr;
			case RendererAPI::API::OpenGL:	return new OpenGLShader(vertexSrc, fragemntSrc);
		}

		ALT_CORE_ASSERT(false, "Unkown RendererAPI!")
		return nullptr;
	}
}