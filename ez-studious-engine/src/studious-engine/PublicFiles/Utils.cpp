#include "Utils.h"


namespace SE
{
	float Utils::EPSILON = std::numeric_limits<float>::epsilon();

	auto Utils::approximatelyEqual(float a, float b, float epsilon) -> bool
	{
		return fabs(a - b) <= ((fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * epsilon);
	}

	auto Utils::essentiallyEqual(float a, float b, float epsilon) -> bool
	{
		return fabs(a - b) <= ((fabs(a) > fabs(b) ? fabs(b) : fabs(a)) * epsilon);
	}

	auto Utils::definitelyGreaterThan(float a, float b, float epsilon) -> bool
	{
		return (a - b) > ((fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * epsilon);
	}

	auto Utils::definitelyLessThan(float a, float b, float epsilon) -> bool
	{
		return (b - a) > ((fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * epsilon);
	}

	auto Utils::rangeIntersection(float minRange1, float maxRange1, float minRange2, float maxRange2) -> bool
	{
		auto min1 = (std::min)(minRange1, maxRange1);
		auto min2 = (std::min)(minRange2, maxRange2);
		auto max1 = (std::max)(minRange1, maxRange1);
		auto max2 = (std::max)(minRange2, maxRange2);

		auto minLessOrEqualToValue1 = essentiallyEqual(min1, min2) || definitelyLessThan(min1, min2);
		auto value1LessOrEqualToMax = essentiallyEqual(min2, max1) || definitelyLessThan(min2, max1);

		auto minLessOrEqualToValue2 = essentiallyEqual(min1, max2) || definitelyLessThan(min1, max2);
		auto value2LessOrEqualToMax = essentiallyEqual(max2, max1) || definitelyLessThan(max2, max1);

		return  (minLessOrEqualToValue1 && value1LessOrEqualToMax) || (minLessOrEqualToValue2 && value2LessOrEqualToMax);
	}

	auto Utils::inRange(float value, float minRange, float maxRange) -> bool
	{
		auto min = (std::min)(minRange, maxRange);
		auto max = (std::max)(minRange, maxRange);
		auto minLessOrEqualToValue = essentiallyEqual(min, value) || definitelyLessThan(min, value);
		auto valueLessOrEqualToMax = essentiallyEqual(value, max) || definitelyLessThan(value, max);

		return minLessOrEqualToValue && valueLessOrEqualToMax;
	}

}