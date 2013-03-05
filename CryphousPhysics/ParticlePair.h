#ifndef __CRYPHOUS_PARTICLE_PAIR_H__
#define __CRYPHOUS_PARTICLE_PAIR_H__

#include <vector>

#include "../CryphousGeometry/Vector3d.h"
#include "Particle.h"

#include "Uncopyable.h"

namespace Cryphous{
	namespace Physics{
		class Particle;
		
class ParticlePair
{
public:

	ParticlePair(){};

	ParticlePair(Particle* particleX, Particle* particleY) :
	  particleX( particleX),
		  particleY( particleY)
	{
	}

	~ParticlePair() { };

public:
	Particle* getParticleX() const { return particleX; }

	Particle* getParticleY() const { return particleY; }

	Geometry::Vector3d getDistanceVector() const { return Geometry::Vector3d( particleY->center, particleX->center); }

	float getDistance() const { return getDistanceVector().getLength(); }

private:
	Particle* particleX;
	Particle* particleY;
};

typedef std::vector<ParticlePair> ParticlePairVector; 
	}
}

#endif