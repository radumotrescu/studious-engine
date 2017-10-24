#pragma once

#include <glew.h>
#include <memory>
#include <vector>

namespace SE
{
	class Buffer
	{
		public:
		Buffer(std::vector<GLfloat> data, GLsizei count, GLuint componentCount);
		auto bind()const->void;
		auto unbind()const->void;
		auto getComponentCount()const->GLuint;
		~Buffer();

	private:
		GLuint m_bufferID;
		GLuint m_componentCount;
	};
}
