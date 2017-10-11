#pragma once

#include <GL\glew.h>
#include <vector>

class IndexBuffer {
private:
	GLuint m_bufferID;
	GLuint m_count;
public:
	IndexBuffer::IndexBuffer(std::vector<GLushort> data, GLsizei count);
	auto bind()->void const;
	auto unbind()->void const;
	auto getCount()->GLuint const;
	~IndexBuffer();
};

