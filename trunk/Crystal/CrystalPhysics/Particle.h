#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include <boost/noncopyable.hpp>
#include <list>
#include <vector>

#include "../CrystalGeom/Point3d.h"
#include "../CrystalGeom/Vector3d.h"

namespace Crystal{
	namespace Geom{
		class Point3d;
		class Vector3d;
	}

	namespace Physics{
		class PhysicsObject;
		class ParticleFactory;
		
class Particle : private boost::noncopyable
{
protected:

	Particle(int id, const Geom::Point3d& center, const double mass, const double radius, ParticleFactory* particleFactory);

	~Particle(void);

	Particle* createClone(const int id = -1) const;

public:

	void resetDiffParameters();

	double getRadius() const { return radius; }

	double getDiameter() const { return radius * 2.0; }

	double getMass() const { return mass; }

	double getVolume() const { return getMass() / density; }

	double getIdealVolume() const;

	double getPressure() const;

	int getID() const { return id; }

	void setParent(PhysicsObject* object) { parent = object; }

	PhysicsObject* getParent() const { return parent; }

	ParticleFactory* getParticleFactory() const { return particleFactory; }

public:
	Geom::Point3d center;
	Geom::Vector3d velocity;
	Geom::Vector3d force;
	double density;

private:
	double radius;
	const int id;
	PhysicsObject* parent;
	const double mass;

	ParticleFactory* particleFactory;

	friend class ParticleFactory;
};

typedef std::vector<Particle*> ParticleVector;
	
	}
}

#endif