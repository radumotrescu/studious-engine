#include "Triangle.h"

namespace SE
{
	Triangle::Triangle()
	{
	}

	auto Triangle::getPoints() const -> std::vector<vec3>
	{
		// the points are assigned counterclockwise starting from the lower left corner
		return std::vector<vec3>(m_points.begin(),m_points.end());
	}

	auto Triangle::getPriority() const -> unsigned
	{
		return m_priority;
	}
	
	auto Triangle::translate(const vec3 & translate) -> void
	{
	}

	auto Triangle::resize(const vec3 & resize) -> void
	{
	}
	
	auto Triangle::getType() const -> Type
	{
		return Type::TRIANGLE;
	}

	auto Triangle::rotate(const vec3 & translate, const vec3 & axis) -> void
	{
	}
	}
