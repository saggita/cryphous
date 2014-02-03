#ifndef __CRYPHOUS_TOLERANCES_H__
#define __CRYPHOUS_TOLERANCES_H__

#include <cmath>

namespace Cryphous{
	namespace Geometry{

class Tolerances
{
public:

	static float getLooseTolerance() { return 1.0e-9f; }

	static float getStrictTolerance() { return 1.0e-18f; }

	static bool isEqualLoosely(float x) { return ::fabs( x ) < getLooseTolerance(); }

	static bool isEqualLoosely(float x, float y) { return ::fabs( x - y ) < getLooseTolerance(); }

	static bool isEqualStrictly(float x) { return ::fabs( x ) < getStrictTolerance(); }

	static bool isEqualStrictly(float x, float y) { 	return ::fabs( x - y ) < getStrictTolerance(); }

	static float getPI() { return 3.14159265359f; }
};

	}
}

#endif