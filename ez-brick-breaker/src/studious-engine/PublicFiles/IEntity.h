#pragma once
namespace SE {
	class IEntity {
	public:
		virtual auto display() -> void = 0;

		virtual ~IEntity() = default;

	};
}