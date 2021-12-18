#include "altpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Alternate
{
	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();
}
