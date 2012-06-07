#ifndef __PARTICLE_CONDITIONS_H__
#define __PARTICLE_CONDITIONS_H__

#include <list>

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
		box( box),
		particleLength( particleLength),
		density( density),
		xNumber(0), yNumber(0), zNumber(0)
		{
			createInnerPoints();
		}

	const Geom::Box& getBox() const { return box; }

	double getParticleLength() const { return particleLength; }

	double getDensity() const { return density; }

	double getParticleVolume() const { return particleLength * particleLength * particleLength; }

	double getParticleMass() const { return density * getParticleVolume(); }

	std::list<Geom::Point3d> getInnerPoints() const { return innerPoints; }
	
	int getXNumber() const { return xNumber; }

	int getYNumber() const { return yNumber; }

	int getZNumber() const { return zNumber; }

protected:
	void createInnerPoints();

private:
	const Geom::Box& box;
	const double particleLength;
	const double density;
	std::list<Geom::Point3d> innerPoints;
	int xNumber;
	int yNumber;
	int zNumber;
};

	}
}

#endif