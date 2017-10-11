#include "Buffer.h"



Buffer::Buffer(std::vector<GLfloat> data, GLsizei count, GLuint componentCount):m_componentCount(componentCount)
{
	glGenBuffers(1, &m_bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), data.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

auto Buffer::bind() -> void const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
}

auto Buffer::unbind() -> void const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

auto Buffer::getComponentCount() -> GLuint const
{
	return m_componentCount;
}

Buffer::~Buffer()
{
}
