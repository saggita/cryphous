#ifndef __RIGID_H__
#define __RIGID_H__

#include "PhysicsObject.h"
#include "RigidEnforcer.h"
#include <list>

namespace Crystal{
	namespace Physics {
		
class Rigid : public PhysicsObject
{
public:
	
	Rigid(const int id, const float density, const float gasConstant, const float viscosityCoefficient, ParticleFactory* particleFactory);

	~Rigid();

	virtual Type getType() { return PhysicsObject::Rigid; }

	virtual void integrateTime(const float proceedTime);

	virtual void enforce(const float proceedTime);

private:
	RigidEnforcer enforcer;
};

	}
}

#endif