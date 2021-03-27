#include "altpch.h"
#include "RendererAPI.h"

#include "Platfrom/OpenGL/OpenGLRendererAPI.h"

namespace Alternate
{
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

	Scope<RendererAPI> RendererAPI::Create()
	{
		switch (s_API)
		{
		case RendererAPI::API::None:    ALT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateScope<OpenGLRendererAPI>();
		}

		ALT_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}