#pragma once

namespace Alternate
{
    class GraphicsContext
    {
    public:
        virtual void* GetRenderContext() = 0;
        virtual void Init() = 0;
        virtual void SwapBuffer() = 0;
        virtual void DeleteRenderContext() = 0;
    };
}