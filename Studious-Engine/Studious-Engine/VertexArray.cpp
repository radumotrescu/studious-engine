#include "VertexArray.h"



VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_arrayID);
}


VertexArray::~VertexArray()
{
	m_buffers.clear();
}

auto VertexArray::addBuffer(std::shared_ptr<Buffer> buffer, GLuint index) ->void
{
	bind();
	buffer->bind();

	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, buffer->getComponentCount(), GL_FLOAT, GL_FALSE, 0, 0);

	buffer->unbind();
	unbind();
}

auto VertexArray::bind()->void
{
	glBindVertexArray(m_arrayID);
}

auto VertexArray::unbind()->void
{
	glBindVertexArray(0);
}