#include "VertexArray.h"

namespace SE
{
	VertexArray::VertexArray()
	{
		const int vertexArrayObjectsNumber = 1;
		glGenVertexArrays(vertexArrayObjectsNumber, &m_arrayID);
	}

	VertexArray::~VertexArray()
	{
		m_buffers.clear();
	}

	auto VertexArray::addBuffer(std::shared_ptr<Buffer>& buffer, GLuint index) const ->void
	{
		bind();
		buffer->bind();

		const int stride = 0;  // Stride is the distance from the beginning of one entity, to the begginging of the following entity.
		const void* offsetPointer = nullptr;
		glVertexAttribPointer(index, buffer->getComponentCount(), GL_FLOAT, GL_FALSE, stride, offsetPointer);
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