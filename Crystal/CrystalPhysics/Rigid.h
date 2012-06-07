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
		PhysicalTimeIntegratorBase* physicalTimeIntegratorBase,
		EnforcerBase* enforcerBase,
		const int xNumber, const int yNumber, const int zNumber );

	~Rigid();

	virtual Type getType() { return PhysicsObject::Rigid; }
};

	}
}

#endif