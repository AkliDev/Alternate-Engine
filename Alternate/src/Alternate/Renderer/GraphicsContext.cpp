#include "altpch.h"
#include "GraphicsContext.h"

#include "Renderer.h"
#include "Platfrom/OpenGL/OpenGLContext.h"

namespace Alternate {

	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    ALT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateScope<OpenGLContext>(static_cast<SDL_Window*>(window));
		}

		ALT_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}
