#ifndef __PARTICLE_CONDITIONS_H__
#define __PARTICLE_CONDITIONS_H__

#include <vector>

namespace Crystal{
	namespace Geom{
		class Point3d;
		class Box;
	}

	namespace Physics{

class ParticleConditions
{
public:
	ParticleConditions(const Geom::Box& box, const double particleLength, const double density) :
		particleLength( particleLength),
		density( density)
		{
			createInnerPoints(box);
		}

	ParticleConditions(const std::vector<Geom::Point3d>& points, const double particleLength, const double density) :
		particleLength( particleLength),
		 density( density),
		 innerPoints( points)
		{
		}

	double getParticleLength() const { return particleLength; }

	double getDensity() const { return density; }

	double getParticleVolume() const { return particleLength * particleLength * particleLength; }

	double getParticleMass() const { return density * getParticleVolume(); }

	std::vector<Geom::Point3d> getInnerPoints() const { return innerPoints; }

protected:
	void createInnerPoints(const Geom::Box& box);

private:
	const double particleLength;
	const double density;
	std::vector<Geom::Point3d> innerPoints;
};

	}
}

#endif