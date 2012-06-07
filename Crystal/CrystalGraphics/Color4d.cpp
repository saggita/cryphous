#include "Color4d.h"

#include <algorithm>

using namespace Crystal::Graphics;

Color4d Color4d::getBlended(const Color4d& rhs, const double rhsRatio)  const {
	const double lhsRatio = 1.0 - rhsRatio;
	Color4d lhsColor = *this;
	lhsColor *= lhsRatio;
	Color4d rhsColor = rhs;
	rhsColor *= rhsRatio;
	lhsColor += rhsColor;
	return lhsColor.normalize();
}

Color4d	Color4d::normalize() {
	red = std::max( 0.0, red );
	green = std::max( 0.0, green );
	blue = std::max( 0.0, blue );
	
	const double maxColor = std::max( red, std::max( green, blue ) );
	(*this) /= maxColor;
	return *this;
}