#pragma once

#include "Entity.h"
#include <iostream>

class Triangle : public IEntity
{
private:
	// the objects in the background get the lowest priority, starting from 0
	// the objects that are superposed on the background get higher priority
	int m_priority;
	std::vector<Point3D> m_points;

	//after any modify of m_matrix, this function will be called
	auto applyChanges()->void;

	//changes coordinates of vertex
	auto changePointCoordinates(const Point3D & vertex)->Point3D;

	//sets m_matrix to identity matrix
	auto resetMatrix()->void;

	//calculate center of entity
	auto calculateCenter()->Point3D;

public:
	Triangle();
	Triangle(Point3D, Point3D, Point3D, int);
public:
	auto getPoints() const->std::vector<Point3D>;
	auto getPriority() const -> int;
	auto getMatrix() const->mat4;

	//translate
	virtual auto translate(const vec3 & translate) -> void override;
	virtual auto resize(const vec3 & resize) -> void override;

	//translate axis in the middle of the screen
	//rotate
	//translate axis in the original position
	virtual auto rotate(const vec3 & rotate, Point3D axis) -> void override;
};