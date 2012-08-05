#ifndef __FLUID_H__
#define __FLUID_H__

#include "../CrystalGeom/Vector3d.h"

#include "PhysicsObject.h"
#include "Particle.h"

#include <boost/foreach.hpp>

namespace Crystal{
	namespace Physics{

class Fluid : public PhysicsObject
{
public:
	Fluid(const int id, const float density, const float gasConstant, const float viscosityCoefficient,ParticleFactory* particleFactory) :
	  PhysicsObject( id, density, gasConstant, viscosityCoefficient,particleFactory )
	  {
	  }

	virtual ~Fluid(void){};

	virtual Type getType() { return PhysicsObject::Fluid; }

	virtual void integrateTime(const float proceedTime) {
		const ParticleVector& particles = getParticles();
		BOOST_FOREACH( Particle* particle, particles ) {
			Geom::Vector3d accelaration = particle->force / particle->density;
			particle->velocity += (accelaration * proceedTime);
			particle->center += (particle->velocity * proceedTime);
		}
	}

	virtual void enforce(const float proceedTime){};
};
	}
}

#endif