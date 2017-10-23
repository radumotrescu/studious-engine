#pragma once

#include <glew.h>
#include <array>
#include <iostream>

#include "IEntity.h"
#include "Vec3.h"

namespace SE
{
	class Triangle : public IEntity
	{
	private:
		unsigned m_priority;
		std::array<vec3,3> m_points;
		std::array<GLfloat,12> m_colorVector;
		std::array<GLfloat, 6> matrix;
		std::array<GLushort,3> indexes = { 1, 2, 3};
	
	public:
		Triangle();

		Triangle(const vec3& vertex1, const vec3& vertex2, const vec3&vertex3, const vec3& color, const unsigned priority);
		Triangle(const std::array<vec3,3>& vertexes, const vec3& color, const unsigned priority);
	public:
		auto getPoints() const->std::vector<vec3>;
		auto getPriority() const -> unsigned override;

		virtual auto translate(const vec3 & translate) -> void override;
		virtual auto resize(const vec3 & resize) -> void override;

		virtual auto getType() const->Type override;

		// Inherited via IEntity
		auto rotate(const vec3 & translate, const vec3 & axis) -> void override;
	};

}