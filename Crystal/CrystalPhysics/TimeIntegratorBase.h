#ifndef __TIME_INTEGRATOR_BASE_H__
#define __TIME_INTEGRATOR_BASE_H__

#include <list>

namespace Crystal{
	namespace Physics{
		class PhysicsObject;

class TimeIntegratorBase
{
public:
	TimeIntegratorBase(void){};
	
	virtual ~TimeIntegratorBase(void){};

	virtual void integrateTime(const PhysicsObject& object, const double proceedTime) = 0;
};

	}
}

#endif