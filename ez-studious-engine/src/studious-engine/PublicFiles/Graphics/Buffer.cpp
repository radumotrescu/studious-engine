#include "Buffer.h"

namespace SE 
{
	Buffer::Buffer(std::vector<GLfloat> data, const GLsizei count, const GLuint componentCount) :m_componentCount(componentCount)
	{
		const int bufferObjectsNumber = 1;
		glGenBuffers(bufferObjectsNumber, &m_bufferID);
		glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), data.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	auto Buffer::bind() const-> void
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
	}

	auto Buffer::unbind() const-> void
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	auto Buffer::getComponentCount() const-> GLuint
	{
		return m_componentCount;
	}

	Buffer::~Buffer()
	{
	}
}
