#include "Triangle.h"

auto Triangle::applyChanges() -> void
{
	for (Point3D & vertex : m_points)
	{
		vertex = changePointCoordinates(vertex);
	}
}

auto Triangle::changePointCoordinates(const Point3D & vertex) -> Point3D
{
	double vertexAsMatrix[MATRIX_DIMENSION][1] = { vertex.x, vertex.y, vertex.z, 1.0f };

	double resultVector[MATRIX_DIMENSION][1];

	//multiply between a matrix and a vector
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

void Triangle::resetMatrix()
{
	for (int i = 0; i < MATRIX_DIMENSION; i++)
	{
		for (int j = 0; j < MATRIX_DIMENSION; j++)
			m_matrix[i][j] = 0;
		m_matrix[i][i] = 1;
	}
}

Triangle::Triangle()
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

	temporaryPoint.x = 0.5;
	temporaryPoint.y = 1.0;
	temporaryPoint.z = 0.0;

	m_points.push_back(temporaryPoint);

	m_priority = 0;
	resetMatrix();
}


Triangle::Triangle(Point3D firstVertex, Point3D secondVertex, Point3D thirdVertex, int priority = 0)
{
	Point3D temporaryPoint;

	temporaryPoint.x = firstVertex.x;
	temporaryPoint.y = firstVertex.y;
	temporaryPoint.z = firstVertex.z;

	m_points.push_back(temporaryPoint);

	temporaryPoint.x = secondVertex.x;
	temporaryPoint.y = secondVertex.y;
	temporaryPoint.z = secondVertex.z;

	m_points.push_back(temporaryPoint);

	temporaryPoint.x = thirdVertex.x;
	temporaryPoint.y = thirdVertex.y;
	temporaryPoint.z = thirdVertex.z;

	m_points.push_back(temporaryPoint);

	m_priority = priority;
	resetMatrix();
}

auto Triangle::getPoints() const -> std::vector<Point3D>
{
	// the points are assigned counterclockwise starting from the lower left corner
	return m_points;
}

auto Triangle::getPriority() const -> int
{
	return m_priority;
}

auto Triangle::getMatrix() const -> mat4
{
	mat4 result;
	for (int j = 0; j < MATRIX_DIMENSION; ++j)
	{
		for (int i = 0; i < MATRIX_DIMENSION; ++i)
		{
			result.elements[MATRIX_DIMENSION * j + i] = m_matrix[i][j];
		}
	}
	return result;
}

auto Triangle::translate(const vec3 & translate) -> void
{
	resetMatrix();

	m_matrix[0][3] = translate.x;
	m_matrix[1][3] = translate.y;
	m_matrix[2][3] = translate.z;

	applyChanges();
}

auto Triangle::resize(const vec3 & translate) -> void
{
}

auto Triangle::rotate(const vec3 & translate, Point3D axis) -> void
{
}
