#pragma once

#include <limits>
#include <algorithm>

namespace SE{
    class Utils{

	public:
		static float EPSILON;
		static auto approximatelyEqual(float a, float b, float epsilon = EPSILON)->bool;
		static auto essentiallyEqual(float a, float b, float epsilon = EPSILON)->bool;
		static auto definitelyGreaterThan(float a, float b, float epsilon = EPSILON)->bool;
		static auto definitelyLessThan(float a, float b, float epsilon = EPSILON)->bool;
		static auto rangeIntersection(float minRange1, float maxRange1, float minRange2, float maxRange2)->bool;
		static auto inRange(float value, float minRange, float maxRange)->bool;
    };
}