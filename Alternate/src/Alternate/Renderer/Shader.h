#pragma once

#include <string>
#include <glm/glm.hpp>
namespace Alternate
{
	class Shader
	{

	public:
		Shader(const std::string& vertexSrc, const std::string& fragemntSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
	private:
		uint32_t m_RendererID = 0;
	};
}