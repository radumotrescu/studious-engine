#pragma once

#include "GL\glew.h"
#include <memory>
#include <vector>

class Buffer {

private:
	GLuint m_bufferID;
	GLuint m_componentCount;
public:
	Buffer(std::vector<GLfloat> data, GLsizei count, GLuint componentCount);
	auto bind()->void const;
	auto unbind()->void const;

	auto getComponentCount()->GLuint const;
	~Buffer();
};

