#include "altpch.h"
#include "VertexArray.h"

#include "Renderer.h"

#include "Platfrom/OpenGL/OpenGLVertexArray.h"

namespace Alternate
{
	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		ALT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!") return nullptr;
		case RendererAPI::API::OpenGL:	return std::make_shared<OpenGLVertexArray>();
		}

		ALT_CORE_ASSERT(false, "Unkown RendererAPI!")
			return nullptr;
	}
}