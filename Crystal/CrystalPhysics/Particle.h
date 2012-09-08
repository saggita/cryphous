#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "Uncopyable.h"
#include <list>
#include <vector>

#include "../CrystalGeom/Vector3d.h"
#include "ParticleConditions.h"

namespace Crystal{
	namespace Physics{
		
class Particle : private Uncopyable
{
protected:

	Particle(int id, const Geom::Vector3d& center, const ParticleConditions& condition) :
		id( id), 
		center( center), 
		condition( condition)
	{
	}

	~Particle(void){};

public:

	void resetDiffParameters()
	{
		normal = Geom::Vector3d( 0.0f, 0.0f, 0.0f );
		density = 0.0;
		force = Geom::Vector3d( 0.0f, 0.0f, 0.0f);
	}

	float getRadius() const { return condition.getParticleLength() * 0.5f; }

	float getDiameter() const { return condition.getParticleLength(); }

	float getMass() const { return condition.getParticleMass(); }

	float getVolume() const { return getMass() / density; }

	float getIdealVolume() const { return std::pow( getRadius() * 2.0f, 2 ); }

	float getPressure() const { return condition.getPressureCoe() * ( std::pow( density / condition.getDensity(), 1 ) - 1.0f ); }

	ParticleConditions getCondition() const { return condition; }

	//void setCondition(const ParticleConditions& condition) { this->condition = condition; }

	int getID() const { return id; }

	bool isIsolated() const { return normal == Geom::Vector3d(0.0f, 0.0f, 0.0f); }

public:
	Geom::Vector3d center;
	Geom::Vector3d velocity;
	Geom::Vector3d force;
	Geom::Vector3d normal;
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