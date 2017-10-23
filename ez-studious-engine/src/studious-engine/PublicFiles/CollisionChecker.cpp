#include "CollisionChecker.h"

namespace SE
{

	auto CollisionChecker::isCollided(IEntity * entity1, IEntity * entity2) const -> bool
	{
		if ((entity1->getType() == Type::RECTANGLE) && (entity2->getType() == Type::RECTANGLE))
		{
			Rectangle* rect1 = dynamic_cast<Rectangle*>(entity1);
			Rectangle* rect2 = dynamic_cast<Rectangle*>(entity2);
			return isCollided(*rect1, *rect2);
		}
		return false;
	}

	auto CollisionChecker::isCollided(Rectangle rect1, Rectangle rect2) const -> bool
	{
		const auto minRange1X = rect1.getOrigin().x;
		const auto maxRange1X = rect1.getOrigin().x + rect1.getWidth();
		const auto minRange2X = rect2.getOrigin().x;
		const auto maxRange2X = rect2.getOrigin().x + rect2.getWidth();

		const auto minRange1Y = rect1.getOrigin().y;
		const auto maxRange1Y = rect1.getOrigin().y + rect1.getHeight();
		const auto minRange2Y = rect2.getOrigin().y;
		const auto maxRange2Y = rect2.getOrigin().y + rect2.getHeight();
		return Utils::rangeIntersection(minRange1X, maxRange1X, minRange2X, maxRange2X) &&
			Utils::rangeIntersection(minRange1Y, maxRange1Y, minRange2Y, maxRange2Y);
	}

	auto CollisionChecker::isCollided(const vec3 point, Rectangle rect) const -> bool
	{
		const auto minRangeX = rect.getOrigin().x;
		const auto maxRangeX = rect.getOrigin().x + rect.getWidth();
		const auto minRangeY = rect.getOrigin().y;
		const auto maxRangeY = rect.getOrigin().y + rect.getHeight();

		return Utils::inRange(point.x, minRangeX, maxRangeX) && Utils::inRange(point.y, minRangeY, maxRangeY);
	}

	auto CollisionChecker::determinant(float a, float b, float c, float d) const ->float
	{
		return a*d - b*c;
	}

	auto CollisionChecker::lineIntersection(vec3 point1, vec3 point2, vec3 point3, vec3 point4, vec3& intersectionPoint) const -> bool
	{
		const auto detL1 = determinant(point1.x, point1.y, point2.x, point2.y);
		const auto detL2 = determinant(point3.x, point3.y, point4.x, point4.y);
		const auto x1mx2 = point1.x - point2.x;
		const auto x3mx4 = point3.x - point4.x;
		const auto y1my2 = point1.y - point2.y;
		const auto y3my4 = point3.y - point4.y;

		const auto xnom = determinant(detL1, x1mx2, detL2, x3mx4);
		const auto ynom = determinant(detL1, y1my2, detL2, y3my4);
		const auto denom = determinant(x1mx2, y1my2, x3mx4, y3my4);

		if (denom == 0.0)
		{
			intersectionPoint.x = NAN;
			intersectionPoint.y = NAN;
			return false;
		}

		intersectionPoint.x = xnom / denom;
		intersectionPoint.y = ynom / denom;

		if (!isfinite(intersectionPoint.x) || !isfinite(intersectionPoint.y))
		{
			return false;
		}

		return true;
	}
}
