#ifndef __PARTICLE_PAIR_H__
#define __PARTICLE_PAIR_H__

#include <vector>

#include "../CrystalGeom/Vector3d.h"
#include "Particle.h"

#include "Uncopyable.h"

namespace Crystal{
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

	Geom::Vector3d getDistanceVector() const { return Geom::Vector3d( particleY->center, particleX->center); }

	float getDistance() const { return getDistanceVector().getLength(); }

private:
	Particle* particleX;
	Particle* particleY;
};

typedef std::vector<ParticlePair> ParticlePairVector; 
	}
}

#endif