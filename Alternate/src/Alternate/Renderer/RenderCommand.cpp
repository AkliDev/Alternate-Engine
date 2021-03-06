#include "altpch.h"
#include "RenderCommand.h"

#include "Platfrom/OpenGL/OpenGLRendererAPI.h"

namespace Alternate
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}