#ifndef __ELASTIC_H__
#define __ELASTIC_H__

#include "../CrystalGeom/Vector3d.h"

#include "PhysicsObject.h"
#include "Particle.h"
#include "SimulationSetting.h"

namespace Crystal{
	namespace Physics{

class Elastic : public PhysicsObject
{
public:
	Elastic(const int id, const float density, const float gasConstant, const float viscosityCoefficient,ParticleFactory* particleFactory) :
	  PhysicsObject( id, density, gasConstant, viscosityCoefficient,particleFactory )
	  {
	  }

	virtual ~Elastic(void){};

	virtual Type getType() { return PhysicsObject::Elastic; }

	virtual void integrateTime(const float proceedTime) {
		const ParticleVector& particles = getParticles();
		if( !particles.empty() ) {
			particles.front()->force = Geom::Vector3d(0.0f, 0.0f, 0.0f);
		}
		for( ParticleVector::const_iterator iter = particles.begin(); iter != particles.end(); ++iter ) {
			Particle* particle = *iter;
			Geom::Vector3d accelaration = particle->force / particle->density;
			particle->velocity += (accelaration * proceedTime);
			particle->center += (particle->velocity * proceedTime);
		}
	}

	virtual void enforce(const float proceedTime){
		const ParticleVector& particles = getParticles();
		if( particles.empty() ){
			return;
		}
		for( size_t i = 0; i < particles.size() -1; ++i ) {
			Particle* particleX = particles[i];
			Particle* particleY = particles[i+1];
			Geom::Vector3d distanceVector = particleX->center - particleY->center;
			const float distance = distanceVector.getLength();
			particleX->force -= getGasConstant() * 1.0f * ( distance - particleX->getDiameter()) * distanceVector / distance;
			particleY->force += getGasConstant() * 1.0f * ( distance - particleY->getDiameter()) * distanceVector / distance;
		}
	};
};
	}
}

#endif