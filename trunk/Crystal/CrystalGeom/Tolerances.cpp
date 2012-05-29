#include "Tolerances.h"

#include <cmath>

using namespace Crystal::Geom;

bool Tolerances::isEqualAsDistance(double x)
{
	return ::fabs( x ) < getDistanceTolerance();
}

bool Tolerances::isEqualAsDistance(double x, double y)
{
	return ::fabs( x - y ) < getDistanceTolerance();
}

bool Tolerances::isEqualAsDenominator(double x)
{
	return ::fabs( x ) < getDenominatorTolerance();
}

bool Tolerances::isEqualAsDenominator(double x, double y)
{
	return ::fabs( x - y ) < getDenominatorTolerance();
}