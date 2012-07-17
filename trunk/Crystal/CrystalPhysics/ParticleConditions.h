#ifndef __PARTICLE_CONDITIONS_H__
#define __PARTICLE_CONDITIONS_H__

#include <vector>

namespace Crystal{
	namespace Geom{
		class Vector3d;
		class Box;
	}

	namespace Physics{

class ParticleConditions
{
public:

	ParticleConditions(const std::vector<Geom::Vector3d>& points, const float particleLength, const float density) :
		particleLength( particleLength),
		 density( density),
		 innerPoints( points)
		{
		}

	float getParticleLength() const { return particleLength; }

	float getDensity() const { return density; }

	float getParticleVolume() const { return particleLength * particleLength * particleLength; }

	float getParticleMass() const { return density * getParticleVolume(); }

	std::vector<Geom::Vector3d> getInnerPoints() const { return innerPoints; }

protected:
	void createInnerPoints(const Geom::Box& box);

private:
	const float particleLength;
	const float density;
	const std::vector<Geom::Vector3d> innerPoints;
};

	}
}

#endif