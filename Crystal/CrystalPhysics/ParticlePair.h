#ifndef __PARTICLE_PAIR_H__
#define __PARTICLE_PAIR_H__

#include <vector>

#include "../CrystalGeom/Vector3d.h"
#include "Particle.h"

#include <boost/noncopyable.hpp>

namespace Crystal{
	namespace Physics{
		class Particle;
		class SpaceHash;
		class BoundarySolver;

class ParticlePair : private boost::noncopyable
{
public:

	ParticlePair();

	ParticlePair(Particle* particleX, Particle* particleY) :
	  particleX( particleX),
		  particleY( particleY),
		  distanceVector( particleY->center, particleX->center )
	{
		distance = distanceVector.getLength();
	}

	~ParticlePair() { };

public:
	Particle* getParticleX() const { return particleX; }

	Particle* getParticleY() const { return particleY; }

	Geom::Vector3d getDistanceVector() const { return distanceVector; }

	double getDistance() const { return distance; }

private:
	Particle* particleX;
	Particle* particleY;
	Geom::Vector3d distanceVector;
	double distance;
};

typedef std::vector<ParticlePair*> ParticlePairVector; 
	}
}

#endif