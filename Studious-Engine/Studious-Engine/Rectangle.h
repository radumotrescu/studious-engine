#pragma once

#include "Entity.h"
#include <iostream>

class Rectangle : public IEntity
{
private:
	// the objects in front of everything get priority 0 
	// the objects in the background get higher priority 
	int m_priority;
	std::vector<Point3D> m_points;

	//after any modify of m_matrix, this function will be called
	auto applyChanges()->void;

	//changes coordinates of vertex
	auto changePointCoordinates(const Point3D & vertex)->Point3D;

	//sets m_matrix to identity matrix
	auto resetMatrix()->void;
public:
	Rectangle();
	Rectangle(Point3D, Point3D, Point3D, Point3D, int);
public:
	auto getPoints() const -> std::vector<Point3D>;
	auto getPriority() const -> int;
	auto getMatrix() const -> mat4;

	virtual auto translate(const vec3& translate) -> void override;
	virtual auto resize(const vec3& resize) -> void override;
	virtual auto rotate(const vec3 & rotate, Point3D axis) -> void override;
};