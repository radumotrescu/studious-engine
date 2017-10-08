#pragma once

#include <glew.h>
#include <vector>
#include <iostream>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Vec3.h"
#include "Vec2.h"
#include "Shader.h"

class Sprite
{

public:
	vec3 m_position;
	vec2 m_dimension;
	Shader m_shader;

	Sprite(const vec3& position, const vec2& dimension, const vec3&color,const unsigned priority);
	auto UpdateLocation(const vec3& position)->void;
	auto UpdateLocation(const vec3& position, const unsigned priority)->void;
	auto Draw()->void;
	auto getPosition()const->vec3;
	auto getColor()const->vec3;
	auto getPriority()const ->unsigned;
	auto action() -> void;

private:
	unsigned int m_priority;
	std::vector<GLfloat> matrixPosition;
	std::vector<GLfloat> colors;
	VertexArray m_vao;
	IndexBuffer ibo;
	std::vector<GLushort> indexes = {
		0,2,3,
		1,2,0
	};
	vec3 m_color;

	GLfloat m_pos1;
	GLfloat m_pos2;
	GLfloat m_pos3;
	GLfloat m_pos4;
};
