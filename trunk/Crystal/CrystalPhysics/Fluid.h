#ifndef __FLUID_H__
#define __FLUID_H__

#include "PhysicsObject.h"

namespace Crystal{
	namespace Physics{

class Fluid : public PhysicsObject
{
public:
	Fluid(const int id, const float density, const float gasConstant, const float viscosityCoefficient,ParticleFactory* particleFactory);

	virtual ~Fluid(void);

	virtual Type getType() { return PhysicsObject::Fluid; }

	virtual void integrateTime(const float proceedTime);

	virtual void enforce(const float proceedTime){};
};

	}
}

#endif