#pragma once

#include <glew.h>
#include <vector>
#include <iostream>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Vec3.h"
#include "Vec2.h"
#include "Shader.h"

class Sprite {

public:
	Sprite();
	Sprite::Sprite(const std::vector<GLfloat>& matrix, const std::vector<GLfloat>& colors, const std::vector<GLushort>&indexes);

	auto Draw()->void;
	//auto action() -> void;

	auto getVAO()->VertexArray;
	auto getIBO()->IndexBuffer;

private:
	VertexArray m_vao;
	IndexBuffer m_ibo;

	auto activateIBO(const std::vector<GLushort>& indexes)->void;
	auto Sprite::activateVAO(const std::vector<GLfloat>& matrix, const std::vector<GLfloat>& colors)->void;
};
