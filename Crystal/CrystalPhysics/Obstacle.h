#ifndef __OBSTACLE_H__
#define __OBSTACLE_H__

#include "PhysicsObject.h"
#include <list>

namespace Crystal{
	namespace Physics {
		
class Obstacle : public PhysicsObject
{
public:
	
	Obstacle(const int id, const double density, const double gasConstant, const double viscosityCoefficient, ParticleFactory* particleFactory);

	~Obstacle();

	virtual Type getType() { return PhysicsObject::Obstacle; }

	virtual void integrateTime(const double proceedTime){};

	virtual void enforce(const double proceedTime){};
};

	}
}

#endif