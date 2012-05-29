#ifndef __PHYSICAL_TIME_INTEGRATOR_H__
#define __PHYSICAL_TIME_INTEGRATOR_H__

#include "PhysicalTimeIntegratorBase.h"

namespace Crystal{
	namespace Physics{

class PhysicalTimeIntegrator : public PhysicalTimeIntegratorBase
{
public:
	PhysicalTimeIntegrator(void);

	~PhysicalTimeIntegrator(void);

	virtual void integrateTime( const PhysicsObject& object, const double proceedTime );
};

	}
}

#endif
