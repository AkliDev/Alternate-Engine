#pragma once

#include <string>
namespace Alternate
{
	class Shader
	{

	public:
		Shader(const std::string& vertexSrc, const std::string& fragemntSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;
	private:
		uint32_t m_RendererID = 0;
	};
}