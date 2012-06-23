#ifndef __TOLERANCES_H__
#define __TOLERANCES_H__

#include <cmath>

namespace Crystal{
	namespace Geom{

class Tolerances
{
public:

	static double getDistanceTolerance() { return 1.0e-9; }

	static double getDenominatorTolerance() { return 1.0e-18; }

	static bool isEqualAsDistance(double x) { return ::fabs( x ) < getDistanceTolerance(); }

	static bool isEqualAsDistance(double x, double y) { return ::fabs( x - y ) < getDistanceTolerance(); }

	static bool isEqualAsDenominator(double x) { return ::fabs( x ) < getDenominatorTolerance(); }

	static bool isEqualAsDenominator(double x, double y) { 	return ::fabs( x - y ) < getDenominatorTolerance(); }

	static double getPI() { return 3.14159265359; }
};

	}
}

#endif