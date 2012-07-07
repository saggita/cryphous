#ifndef __RIGID_H__
#define __RIGID_H__

#include "PhysicsObject.h"
#include <list>

namespace Crystal{
	namespace Physics {
		
class Rigid : public PhysicsObject
{
public:
	
	Rigid(const int id, const double density, const double gasConstant, const double viscosityCoefficient,
		ParticleFactory* particleFactory,
		EnforcerBase* enforcerBase);

	~Rigid();

	virtual Type getType() { return PhysicsObject::Rigid; }

	virtual void integrateTime(const double proceedTime);
};

	}
}

#endif