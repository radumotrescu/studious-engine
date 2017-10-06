#pragma once

#include <vector>
#include"Mat4.h"
#include"Vec3.h"

const int MATRIX_DIMENSION = 4;

struct Point3D
{
	float x;
	float y;
	float z;
};

class IEntity
{
protected:
	float m_matrix[MATRIX_DIMENSION][MATRIX_DIMENSION];

public:
	virtual auto getPoints() const -> std::vector<Point3D> = 0;
	virtual auto getPriority() const -> int = 0;
	virtual auto getMatrix() const -> mat4 = 0;

	virtual auto translate(const vec3 & translate) -> void = 0;
	virtual auto resize(const vec3& translate) -> void = 0;
	virtual auto rotate(const vec3& translate, Point3D axis) -> void = 0;
};