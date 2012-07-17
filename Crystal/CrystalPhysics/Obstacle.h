#ifndef __OBSTACLE_H__
#define __OBSTACLE_H__

#include "PhysicsObject.h"
#include <list>

namespace Crystal{
	namespace Physics {
		
class Obstacle : public PhysicsObject
{
public:
	
	Obstacle(const int id, const float density, const float gasConstant, const float viscosityCoefficient, ParticleFactory* particleFactory);

	~Obstacle();

	virtual Type getType() { return PhysicsObject::Obstacle; }

	virtual void integrateTime(const float proceedTime){};

	virtual void enforce(const float proceedTime){};
};

	}
}

#endif