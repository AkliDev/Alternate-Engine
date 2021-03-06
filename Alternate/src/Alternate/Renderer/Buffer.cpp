#include "altpch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Platfrom/OpenGL/OpenGLBuffer.h"

namespace Alternate
{
	VertexBuffer* VertexBuffer::Create(float* vetices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:	ALT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!") return nullptr;
			case RendererAPI::API::OpenGL:	return new OpenGLVertexBuffer(vetices, size);
		}

		ALT_CORE_ASSERT(false, "Unkown RendererAPI!")
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:	ALT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!") return nullptr;
			case RendererAPI::API::OpenGL:	return new OpenGLIndexBuffer(indices, size);
		}

		ALT_CORE_ASSERT(false, "Unkown RendererAPI!")
		return nullptr;
	}
}