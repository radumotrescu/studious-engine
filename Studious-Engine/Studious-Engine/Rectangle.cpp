#include "Rectangle.h"

auto Rectangle::applyChanges() -> void
{
	for (Point3D & vertex : m_points)
	{
		vertex = changePointCoordinates(vertex);
	}
}

auto Rectangle::changePointCoordinates(const Point3D & vertex) -> Point3D
{
	double vertexAsMatrix[MATRIX_DIMENSION][1] = { vertex.x, vertex.y, vertex.z, 1.0f };
	
	double resultVector[MATRIX_DIMENSION][1];
	for (int i = 0; i<MATRIX_DIMENSION; i++)
	{
		double aux = 0;
		for (int j = 0; j<MATRIX_DIMENSION; j++)
			aux = aux + m_matrix[i][j] * vertexAsMatrix[j][0];
		resultVector[i][0] = aux;
	}
	Point3D result;
	result.x = resultVector[0][0];
	result.y = resultVector[1][0];
	result.z = resultVector[2][0];
	return result;
}

void Rectangle::resetMatrix()
{
	for (int i = 0; i < MATRIX_DIMENSION; i++)
	{
		for (int j = 0; j < MATRIX_DIMENSION; j++)
			m_matrix[i][j] = 0;
		m_matrix[i][i] = 1;
	}
}

Rectangle::Rectangle()
{
	// the points are assigned counterclockwise starting from the lower left corner
	Point3D temporaryPoint;
	
	temporaryPoint.x = 0.0;
	temporaryPoint.y = 0.0;
	temporaryPoint.z = 0.0;

	m_points.push_back(temporaryPoint);

	temporaryPoint.x = 1.0;
	temporaryPoint.y = 0.0;
	temporaryPoint.z = 0.0;

	m_points.push_back(temporaryPoint);

	temporaryPoint.x = 1.0;
	temporaryPoint.y = 1.0;
	temporaryPoint.z = 0.0;

	m_points.push_back(temporaryPoint);

	temporaryPoint.x = 0.0;
	temporaryPoint.y = 1.0;
	temporaryPoint.z = 0.0;

	m_points.push_back(temporaryPoint);

	m_priority = 0;

	resetMatrix();
}

Rectangle::Rectangle(Point3D lowerLeftVertex, Point3D lowerRightVertex, Point3D upperRightVertex, Point3D upperLeftVertex, int priority = 0)
{
	Point3D temporaryPoint;

	temporaryPoint.x = lowerLeftVertex.x;
	temporaryPoint.y = lowerLeftVertex.y;
	temporaryPoint.z = lowerLeftVertex.z;

	m_points.push_back(temporaryPoint);

	temporaryPoint.x = lowerRightVertex.x;
	temporaryPoint.y = lowerRightVertex.y;
	temporaryPoint.z = lowerRightVertex.z;

	m_points.push_back(temporaryPoint);

	temporaryPoint.x = upperRightVertex.x;
	temporaryPoint.y = upperRightVertex.y;
	temporaryPoint.z = upperRightVertex.z;

	m_points.push_back(temporaryPoint);

	temporaryPoint.x = upperLeftVertex.x;
	temporaryPoint.y = upperLeftVertex.y;
	temporaryPoint.z = upperLeftVertex.z;

	m_points.push_back(temporaryPoint);

	m_priority = priority;

	resetMatrix();
}

auto Rectangle::getPoints() const -> std::vector<Point3D>
{
	// the points are assigned counterclockwise starting from the lower left corner
	return m_points;
}

auto Rectangle::getPriority() const -> int
{
	return m_priority;
}

auto Rectangle::getMatrix() const -> mat4
{
	mat4 result;
	for (int j = 0; j < 4; ++j)
	{
		for (int i = 0; i < 4; ++i)
		{
			result.elements[4 * j + i] = m_matrix[i][j];
		}
	}
	return result;
}

auto Rectangle::translate(const vec3& translate) -> void
{
	resetMatrix();
	m_matrix[0][3] = translate.x;
	m_matrix[1][3] = translate.y;
	m_matrix[2][3] = translate.z;

	applyChanges();
}

auto Rectangle::resize(const vec3 & translate) -> void
{
}

auto Rectangle::rotate(const vec3 & translate, Point3D axis) -> void
{
}