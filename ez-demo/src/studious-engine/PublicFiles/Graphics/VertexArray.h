#pragma once

#include <glew.h>
#include <memory>
#include <vector>

#include "Buffer.h"

namespace SE
{
	class VertexArray 
	{
	public:
		VertexArray();
		~VertexArray();
		auto addBuffer(std::shared_ptr<Buffer>& buffer, GLuint index) const ->void;
		auto bind()const ->void;
		auto unbind()const ->void;

	private:
		GLuint m_arrayID;
		std::vector<std::shared_ptr<Buffer>>m_buffers;
	};
}
