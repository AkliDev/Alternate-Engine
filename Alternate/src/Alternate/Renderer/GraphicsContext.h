#pragma once

namespace Alternate
{
    class GraphicsContext
    {
    public:
        virtual ~GraphicsContext() = default;
       
        virtual void Init() = 0;
        virtual void SwapBuffer() = 0;
        virtual void* GetRenderContext() = 0;
        virtual void DeleteRenderContext() = 0;

		static Scope<GraphicsContext> Create(void* window);
    };
}
