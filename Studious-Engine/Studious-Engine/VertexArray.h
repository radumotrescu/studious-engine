#pragma once

#include "GL\glew.h"
#include <memory>
#include <vector>

#include "Buffer.h"

class VertexArray {
private:

	GLuint m_arrayID;
	std::vector<std::shared_ptr<Buffer>>m_buffers;

public:
	VertexArray();
	~VertexArray();

	auto addBuffer(std::shared_ptr<Buffer>& buffer, GLuint index)->void;
	auto bind()const ->void;
	auto unbind()const ->void;
};

