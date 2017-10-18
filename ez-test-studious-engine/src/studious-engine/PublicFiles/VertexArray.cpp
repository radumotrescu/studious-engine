#include "VertexArray.h"

namespace SE {

	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &m_arrayID);
	}


	VertexArray::~VertexArray()
	{
		m_buffers.clear();
	}

	auto VertexArray::addBuffer(std::shared_ptr<Buffer>& buffer, GLuint index) ->void
	{
		bind();
		buffer->bind();

		glVertexAttribPointer(index, buffer->getComponentCount(), GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(index);

		buffer->unbind();
		unbind();
	}

	auto VertexArray::bind()const ->void
	{
		glBindVertexArray(m_arrayID);
	}

	auto VertexArray::unbind()const ->void
	{
		glBindVertexArray(0);
	}

}