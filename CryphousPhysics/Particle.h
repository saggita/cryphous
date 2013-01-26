#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "Uncopyable.h"
#include <list>
#include <vector>

#include "../CryphousGeometry/Vector3d.h"
#include "ParticleConditions.h"

namespace Cryphous{
	namespace Physics{
		
class Particle : private Uncopyable
{
protected:

	Particle(int id, const Geometry::Vector3d& center, const ParticleConditions& condition) :
		id( id), 
		center( center), 
		condition( condition)
	{
	}

	~Particle(void){};

public:

	void resetDiffParameters()
	{
		normal = Geometry::Vector3d( 0.0f, 0.0f, 0.0f );
		density = 0.0;
		force = Geometry::Vector3d( 0.0f, 0.0f, 0.0f);
	}

	float getRadius() const { return condition.getParticleLength() * 0.5f; }

	float getDiameter() const { return condition.getParticleLength(); }

	float getMass() const { return condition.getParticleMass(); }

	float getVolume() const { return getMass() / density; }

	float getIdealVolume() const { return std::pow( getRadius() * 2.0f, 2 ); }

	float getPressure() const { return condition.getPressureCoe() * ( std::pow( density / condition.getDensity(), 1 ) - 1.0f ); }

	ParticleConditions getCondition() const { return condition; }

	int getID() const { return id; }

	bool isIsolated() const { return normal == Geometry::Vector3d(0.0f, 0.0f, 0.0f); }

public:
	Geometry::Vector3d center;
	Geometry::Vector3d velocity;
	Geometry::Vector3d force;
	Geometry::Vector3d normal;
	float density;

private:
	const int id;
	ParticleConditions condition;

	friend class ParticleFactory;
};

typedef std::vector<Particle*> ParticleVector;
	
	}
}

#endif