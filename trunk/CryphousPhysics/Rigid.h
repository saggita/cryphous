#ifndef __RIGID_H__
#define __RIGID_H__

#include "../CryphousGeometry/Vector3d.h"

#include "PhysicsObject.h"
#include "RigidEnforcer.h"
#include <list>

namespace Cryphous{
	namespace Physics {
		
class Rigid : public PhysicsObject
{
public:
	
	Rigid(const int id, const float density, const float gasConstant, const float viscosityCoefficient, ParticleFactory* particleFactory) :
	  PhysicsObject( id , density, gasConstant, viscosityCoefficient, particleFactory)
	  {
	  }

	  ~Rigid(){};

	virtual Type getType() { return PhysicsObject::Rigid; }

	virtual void integrateTime(const float proceedTime) {
		const ParticleVector& particles = getParticles();
		for( ParticleVector::const_iterator iter = particles.begin(); iter != particles.end(); ++iter ) {
			Particle* particle = *(iter);
			const Geometry::Vector3d& accelaration = particle->force / particle->density;
			particle->velocity += (accelaration * proceedTime);
			particle->center += (particle->velocity * proceedTime);
		}
	}

	virtual void enforce(const float proceedTime) {
		enforcer.enforce( this, proceedTime);
	}

private:
	RigidEnforcer enforcer;
};

	}
}

#endif