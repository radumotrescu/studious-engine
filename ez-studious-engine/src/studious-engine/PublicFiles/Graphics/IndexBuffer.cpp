#include "IndexBuffer.h"

namespace SE 
{

	IndexBuffer::IndexBuffer()
	{
	}

	IndexBuffer::IndexBuffer(std::vector<GLushort> data, const GLsizei count) : m_count(count)
	{
		const int bufferObjectsNumber = 1;
		glGenBuffers(bufferObjectsNumber, &m_bufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLushort), data.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	auto IndexBuffer::bind()const -> void
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID);
	}

	auto IndexBuffer::unbind() const-> void
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	auto IndexBuffer::getCount()const -> GLuint
	{
		return m_count;
	}

	IndexBuffer::~IndexBuffer()
	{
	}
}
