#pragma once

#include <vector>

#include"Vec3.h"

namespace SE
{
	struct Point3D
	{
		float x;
		float y;
		float z;
	};
	enum class Type
	{
		RECTANGLE,
		TRIANGLE,
		CIRCLE,
		UNDEFINED
	};

	class IEntity
	{
	public:
		virtual auto display() -> void = 0;

		virtual auto getPriority() const -> unsigned = 0;
		virtual auto getType() const->Type = 0;

		virtual auto translate(const vec3 & translate) -> void = 0;
		virtual auto resize(const vec3& translate) -> void = 0;
		virtual auto rotate(const vec3& translate, const vec3& axis) -> void = 0;

		virtual ~IEntity() = default;
	};
}