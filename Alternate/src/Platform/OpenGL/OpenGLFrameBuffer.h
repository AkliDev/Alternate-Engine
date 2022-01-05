#pragma once

#include "Alternate/Renderer/FrameBuffer.h"

namespace Alternate
{
	class OpenGLFrameBuffer : public FrameBuffer
	{
	public:
		OpenGLFrameBuffer(const FramebufferSpecification& specification);
		virtual ~OpenGLFrameBuffer();

		void Invalidate();

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual void Resize(const uint32_t width, const uint32_t height) override;

		virtual uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const override { ALT_CORE_ASSERT(index < m_ColorAttachments.size()); return m_ColorAttachments[index]; }

		virtual const FramebufferSpecification& GetSpecification() const override { return m_Specification; }
	private:
		uint32_t m_RendererID = 0;

		FramebufferSpecification m_Specification;

		std::vector<FramebufferTextureSpecification> m_ColorAttachmentSpecifications;
		FramebufferTextureSpecification m_DepthAttachmentSpecification = FramebufferTextureFormat::None;

		std::vector<uint32_t> m_ColorAttachments;
		uint32_t m_DepthAttachment;

	};
}
