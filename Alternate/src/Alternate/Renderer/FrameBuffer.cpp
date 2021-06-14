#include "altpch.h"

#include "FrameBuffer.h"
#include "Renderer.h"

#include "Platfrom/OpenGL/OpenGLFrameBuffer.h"

namespace Alternate
{
	Ref<Alternate::FrameBuffer> FrameBuffer::Create(const FramebufferSpecification& spec)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:	ALT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!") return nullptr;
		case RendererAPI::API::OpenGL:	return CreateRef<OpenGLFrameBuffer>(spec);
		}

		ALT_CORE_ASSERT(false, "Unkown RendererAPI!")
			return nullptr;
	}
}