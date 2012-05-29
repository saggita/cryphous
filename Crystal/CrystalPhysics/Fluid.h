#pragma once

#include "PhysicsObject.h"

namespace Crystal{
	namespace Physics{

class Fluid : public PhysicsObject
{
public:
	Fluid(const int id, const double density, const double gasConstant, const double viscosityCoefficient,ParticleFactory* particleFactory);

	virtual ~Fluid(void);

	virtual Type getType() { return PhysicsObject::Fluid; }
};

	}
}