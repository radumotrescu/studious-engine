#pragma once

#include <glew.h>
#include <vector>

namespace SE {
	class IndexBuffer {

	public:
		IndexBuffer();
		IndexBuffer::IndexBuffer(std::vector<GLushort> data, const GLsizei count);
		auto bind()const->void;
		auto unbind()const->void;
		auto getCount()const->GLuint;
		~IndexBuffer();

	private:
		GLuint m_bufferID;
		GLuint m_count;
	};

}
