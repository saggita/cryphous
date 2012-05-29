#ifndef __PHYSICAL_TIME_INTEGRATOR_BASE_H__
#define __PHYSICAL_TIME_INTEGRATOR_BASE_H__

#include <list>
#include <boost/noncopyable.hpp>

#include "TimeIntegratorBase.h"

namespace Crystal{
	namespace Physics{
		class PhysicsObject;

class PhysicalTimeIntegratorBase : public TimeIntegratorBase, private boost::noncopyable
{
public:
	PhysicalTimeIntegratorBase(void){};

	virtual ~PhysicalTimeIntegratorBase(void){};

	virtual void integrateTime(const PhysicsObject& object, const double proceedTime);
};

	}
}

#endif
