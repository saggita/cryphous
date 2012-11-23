#ifndef __TOLERANCES_H__
#define __TOLERANCES_H__

namespace Amorphous{
	namespace Geom{

class Tolerances
{
public:

	static double getDistanceTolerance() { return 1.0e-9; }

	static double getDenominatorTolerance() { return 1.0e-18; }

	static bool isEqualAsDistance(double x);

	static bool isEqualAsDistance(double x, double y);

	static bool isEqualAsDenominator(double x);

	static bool isEqualAsDenominator(double x, double y);

	static double getPI() { return 3.14159265359; }
};

	}
}

#endif