#ifndef __TOLERANCES_H__
#define __TOLERANCES_H__

#include <cmath>

namespace Crystal{
	namespace Geom{

class Tolerances
{
public:

	static float getDistanceTolerance() { return 1.0e-9f; }

	static float getDenominatorTolerance() { return 1.0e-18f; }

	static bool isEqualAsDistance(float x) { return ::fabs( x ) < getDistanceTolerance(); }

	static bool isEqualAsDistance(float x, float y) { return ::fabs( x - y ) < getDistanceTolerance(); }

	static bool isEqualAsDenominator(float x) { return ::fabs( x ) < getDenominatorTolerance(); }

	static bool isEqualAsDenominator(float x, float y) { 	return ::fabs( x - y ) < getDenominatorTolerance(); }

	static float getPI() { return 3.14159265359f; }
};

	}
}

#endif