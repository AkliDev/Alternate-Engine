#include "altpch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"


namespace Alternate
{
	Ref<Texture2D> Texture2D::Create(const uint32_t width, const uint32_t height)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:	ALT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!") return nullptr;
		case RendererAPI::API::OpenGL:	return CreateRef<OpenGLTexture2D>(width, height);
		}

		ALT_CORE_ASSERT(false, "Unkown RendererAPI!")
		return nullptr;
	}

	//TODO add something like a texture library and return an already existing texture if the requested texture is the same.
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:	ALT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!") return nullptr;
			case RendererAPI::API::OpenGL:	return CreateRef<OpenGLTexture2D>(path);
		}

		ALT_CORE_ASSERT(false, "Unkown RendererAPI!")
		return nullptr;
	}
}
