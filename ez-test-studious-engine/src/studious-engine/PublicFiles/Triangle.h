#pragma once

#include "IEntity.h"
#include "Vec3.h"

#include <glew.h>
#include <array>
#include <iostream>

namespace SE {
	class Triangle : public IEntity {
	private:
		unsigned m_priority;
		std::array<vec3,3> m_points;
		std::array<GLfloat,12> m_colorVector;
		std::array<GLfloat, 6> matrix;
		std::array<GLushort,3> indexes = { 1, 2, 3};


		auto changePointCoordinates(const Point3D & vertex)->Point3D;

	public:
		Triangle();

		Triangle(const vec3& vertex1, const vec3& vertex2, const vec3&vertex3, const vec3& color, const unsigned priority);
		Triangle(const std::array<vec3,3>& vertexes, const vec3& color, const unsigned priority);
	public:
		auto getPoints() const->std::vector<vec3>;
		auto getPriority() const -> unsigned;

		virtual auto translate(const vec3 & translate) -> void override;
		virtual auto resize(const vec3 & resize) -> void override;

		virtual auto getType() const->Type override;

		// Inherited via IEntity
		virtual auto rotate(const vec3 & translate, const vec3 & axis) -> void;
	};

}