#include "altpch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platfrom/OpenGL/OpenGLTexture.h"


namespace Alternate
{
	Ref<Alternate::Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:	ALT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!") return nullptr;
			//case RendererAPI::API::OpenGL:	return std::make_shared<Texture2D>(path);
		}

		ALT_CORE_ASSERT(false, "Unkown RendererAPI!")
		return nullptr;
	}
}