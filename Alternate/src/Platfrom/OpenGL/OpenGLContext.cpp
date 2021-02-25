#include "altpch.h"
#include "OpenGLContext.h"

#include <SDL.h>
#include <glad/glad.h>

namespace Alternate
{
 
    OpenGLContext::OpenGLContext(SDL_Window* windowHandle)
        :m_WindowHandle(windowHandle)
    {
        ALT_CORE_ASSERT(windowHandle, "Window handle is null!")
    }

    void OpenGLContext::Init()
    {
        SDL_GL_LoadLibrary(NULL); // Default OpenGL is fine.

        // Request an OpenGL 4.6 context (should be core)
        SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
        // Also request a depth buffer
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
        //enable debug context
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);

        m_Context = SDL_GL_CreateContext(m_WindowHandle);
        SDL_GL_MakeCurrent(m_WindowHandle, m_Context);

        int status = gladLoadGLLoader(SDL_GL_GetProcAddress);
        ALT_CORE_ASSERT(status, "failed to initialize Glad!");

        ALT_CORE_INFO("OpenGL Info:");
        ALT_CORE_INFO("  Vendor:    {0}", glGetString(GL_VENDOR));
        ALT_CORE_INFO("  Renderer:  {0}", glGetString(GL_RENDERER));
        ALT_CORE_INFO("  Version:   {0}", glGetString(GL_VERSION));
    }

    void OpenGLContext::SwapBuffer()
    {
        SDL_GL_SwapWindow(m_WindowHandle);      
    }

    void OpenGLContext::DeleteRenderContext()
    {
        SDL_GL_DeleteContext(m_Context);
    }
}