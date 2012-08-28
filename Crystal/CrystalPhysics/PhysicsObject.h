#ifndef __PHYSICS_OBJECT_H__
#define __PHYSICS_OBJECT_H__

#include "../CrystalUtility/Uncopyable.h"
#include <list>

#include "Particle.h"
#include "ParticleFactory.h"
#include "../CrystalGeom/Vector3d.h"

#include <boost/foreach.hpp>

namespace Crystal{
	namespace Physics{
		class PhysicsObjectFactory;

class PhysicsObject : private Uncopyable
{
protected:
	PhysicsObject(const int id, const float density, const float gasConstant, const float viscosityCoefficient, ParticleFactory* particleFactory) :
		 id( id), density( density), gasConstant( gasConstant), viscosityCoefficient( viscosityCoefficient), particleFactory( particleFactory)
		 {
		 }

		 virtual ~PhysicsObject(void){};

public:
	enum Type{
		Fluid,
		Rigid,
		Obstacle,
	};

	virtual Type getType() = 0;

	int getID() const { return id; }

	ParticleVector getParticles() const { return particleFactory->getParticles(); }

	virtual void enforce(const float proceedTime) = 0;

	virtual void integrateTime(const float proceedTime ) = 0;

	Geom::Vector3d getCenter() const {
		if( getParticles().empty() ) {
			return Geom::Vector3d( 0.0, 0.0, 0.0);
		}
		Geom::Vector3d center( 0.0, 0.0, 0.0);
		BOOST_FOREACH(Particle* particle, getParticles()) {
			center += particle->center;
		}
		return center /= static_cast<float>(getParticles().size());
	}

	Geom::Vector3d getAverageVelosity() const {
		Geom::Vector3d averageVelosity( 0.0, 0.0, 0.0 );
		BOOST_FOREACH( Particle* particle, getParticles() ) {
			averageVelosity += particle->velocity;
		}
		return averageVelosity / static_cast<float>(getParticles().size());
	}

	float getWeight() const {
		float weight = 0.0;
		BOOST_FOREACH(Particle* particle, getParticles()) {
			weight += particle->getMass();
		}
		return weight;
	}

	float getDensity() const {return density; }

	float getGasConstant() const { return gasConstant; }

	float getViscosityCoefficient() const { return viscosityCoefficient; }

	ParticleFactory* getParticleFactory() const { return particleFactory; }

private:
	const int id;
	const float density;
	const float gasConstant;
	const float viscosityCoefficient;
	ParticleFactory* particleFactory;
	
	friend PhysicsObjectFactory;
};

class PhysicsObject;
typedef std::list<PhysicsObject*> PhysicsObjectList;

	}
}
#endif