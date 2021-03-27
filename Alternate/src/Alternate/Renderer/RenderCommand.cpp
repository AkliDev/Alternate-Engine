#include "altpch.h"
#include "RenderCommand.h"

#include "Platfrom/OpenGL/OpenGLRendererAPI.h"

namespace Alternate
{
	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();
}