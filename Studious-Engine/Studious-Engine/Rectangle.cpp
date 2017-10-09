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
	float vertexAsMatrix[MATRIX_DIMENSION][1] = { vertex.x, vertex.y, vertex.z, 1.0f };

	float resultVector[MATRIX_DIMENSION][1];
	for (int i = 0; i < MATRIX_DIMENSION; i++)
	{
		float aux = 0;
		for (int j = 0; j < MATRIX_DIMENSION; j++)
			aux = aux + m_matrix[i][j] * vertexAsMatrix[j][0];
		resultVector[i][0] = aux;
	}
	Point3D result;
	result.x = resultVector[0][0];
	result.y = resultVector[1][0];
	result.z = resultVector[2][0];
	return result;
}

auto Rectangle::resetMatrix()->void
{
	for (int i = 0; i < MATRIX_DIMENSION; i++)
	{
		for (int j = 0; j < MATRIX_DIMENSION; j++)
			m_matrix[i][j] = 0;
		m_matrix[i][i] = 1;
	}
}

auto Rectangle::calculateCenter() -> Point3D
{
	float x = 0, y = 0, z = 0;
	for (auto point : m_points)
	{
		x += point.x;
		y += point.y;
		z += point.z;
	}
	float size = m_points.size();
	Point3D result = { x / size, y / size, z / size };
	return result;
}

Rectangle::Rectangle()
{
	// the points are assigned clockwise starting from the upper left corner
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

	m_width = 1.0f;
	m_height = 1.0f;
	resetMatrix();
}

Rectangle::Rectangle(Point3D upperLeftVertex, float width, float height, int priority = 0)
{
	Point3D temporaryPoint;
	m_points.push_back(upperLeftVertex);

	temporaryPoint = { upperLeftVertex.x + width, upperLeftVertex.y, upperLeftVertex.z };
	m_points.push_back(temporaryPoint);

	temporaryPoint = { upperLeftVertex.x + width, upperLeftVertex.y+height, upperLeftVertex.z };
	m_points.push_back(temporaryPoint);

	temporaryPoint = { upperLeftVertex.x, upperLeftVertex.y+height, upperLeftVertex.z };
	m_points.push_back(temporaryPoint);

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

auto Rectangle::resize(const vec3 & resize) -> void
{
	auto center = calculateCenter();

	//translate center to origin
	translate(vec3(-center.x, -center.y, -center.z));

	//resize
	resetMatrix();
	m_matrix[0][0] = resize.x;
	m_matrix[1][1] = resize.y;
	m_matrix[2][2] = resize.z;
	applyChanges();

	//translate center back to original position
	translate(vec3(center.x, center.y, center.z));
}

auto Rectangle::rotate(const vec3 & rotate, Point3D axis) -> void
{
	//translate axis to origin
	translate(vec3(-axis.x, -axis.y, -axis.z));

	//rotate
	resetMatrix();
	m_matrix[0][0] = cos(rotate.x);
	m_matrix[0][1] = -sin(rotate.y);
	m_matrix[1][0] = sin(rotate.x);
	m_matrix[1][1] = cos(rotate.y);
	applyChanges();

	//translate axis to original position
	translate(vec3(axis.x, axis.y, axis.z));
}

auto Rectangle::getWidth() -> float const
{
	return m_width;
}

auto Rectangle::getHeight() -> float const
{
	return m_height;
}

auto Rectangle::getOrigin() -> Point3D const
{
	return m_points[0];
}

auto Rectangle::getType() const -> Type
{
	return Type::RECTANGLE;
}
