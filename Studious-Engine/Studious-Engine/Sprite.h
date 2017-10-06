#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Vec4.h"
#include "Vec3.h"

#include <glew.h>
#include <vector>

class Sprite {
private:
	unsigned int m_priority;
	std::vector<GLfloat> matrixPosition;
	std::vector<GLfloat> colors;
	VertexArray vao;
	IndexBuffer ibo;

	std::vector<GLushort> indexes = {
		0,2,3,
		1,2,0
	};

	vec4 m_position;
	vec3 m_color;

	GLfloat m_pos1;
	GLfloat m_pos2;
	GLfloat m_pos3;
	GLfloat m_pos4;

public:
	Sprite(GLfloat pos1, GLfloat pos2, GLfloat pos3, GLfloat pos4, GLfloat R, GLfloat G, GLfloat B);

	Sprite(const vec4& position, const vec3& color,const unsigned priority);

	auto UpdateLocation(const GLfloat pos1, const GLfloat pos2, const  GLfloat pos3, const  GLfloat pos4)->void;

	auto UpdateLocation(const vec4& position)->void;

	auto UpdateLocation(const vec4& position, const unsigned priority)->void;

	auto Draw()->void;

	auto getPosition()const->vec4;
	auto getColor()const->vec3;
	auto getPriority()const ->unsigned;
};