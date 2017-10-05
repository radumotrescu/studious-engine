#pragma once

#include <GL\glew.h>
#include <vector>

class IndexBuffer {
private:
	GLuint m_bufferID;
	GLuint m_count;
public:
	IndexBuffer();
	IndexBuffer::IndexBuffer(std::vector<GLushort> data, GLsizei count);
	auto bind()const->void ;
	auto unbind()const->void ;
	auto getCount()const->GLuint;
	~IndexBuffer();
};

