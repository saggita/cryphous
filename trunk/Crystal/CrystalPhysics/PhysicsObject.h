#ifndef __PHYSICS_OBJECT_H__
#define __PHYSICS_OBJECT_H__

#include <boost/noncopyable.hpp>
#include <list>

#include "ParticleFactory.h"

namespace Crystal{

	namespace Geom{
		class Vector3d;
		class Vector3d;
	}

	namespace Physics{
		class Particle;
		typedef std::vector<Particle*> ParticleVector;
		class PhysicsObjectFactory;


class PhysicsObject : private boost::noncopyable
{
protected:
	PhysicsObject(const int id, const float density, const float gasConstant, const float viscosityCoefficient, ParticleFactory* particleFactory);

	virtual ~PhysicsObject(void);

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

	Geom::Vector3d getCenter() const;

	Geom::Vector3d getAverageVelosity() const;

	float getWeight() const;

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