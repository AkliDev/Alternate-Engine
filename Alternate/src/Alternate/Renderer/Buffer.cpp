#include "altpch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Platfrom/OpenGL/OpenGLBuffer.h"

namespace Alternate
{
	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:	ALT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!") return nullptr;
		case RendererAPI::API::OpenGL:	return CreateRef<OpenGLVertexBuffer>(size);
		}

		ALT_CORE_ASSERT(false, "Unkown RendererAPI!")
			return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::Create(float* vetices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:	ALT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!") return nullptr;
			case RendererAPI::API::OpenGL:	return CreateRef<OpenGLVertexBuffer>(vetices, size);
		}

		ALT_CORE_ASSERT(false, "Unkown RendererAPI!")
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:	ALT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!") return nullptr;
			case RendererAPI::API::OpenGL:	return CreateRef<OpenGLIndexBuffer>(indices, count);
		}

		ALT_CORE_ASSERT(false, "Unkown RendererAPI!")
		return nullptr;
	}
}