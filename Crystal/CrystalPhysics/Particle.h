#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include <boost/noncopyable.hpp>
#include <list>
#include <vector>

#include "../CrystalGeom/Vector3d.h"

namespace Crystal{
	namespace Geom{
		class Vector3d;
	}

	namespace Physics{
		class PhysicsObject;
		class ParticleFactory;
		
class Particle : private boost::noncopyable
{
protected:

	Particle(int id, const Geom::Vector3d& center, const float mass, const float radius, ParticleFactory* particleFactory);

	~Particle(void);

	Particle* createClone(const int id = -1) const;

public:

	void resetDiffParameters();

	float getRadius() const { return radius; }

	float getDiameter() const { return radius * 2.0f; }

	float getMass() const { return mass; }

	float getVolume() const { return getMass() / density; }

	float getIdealVolume() const;

	float getPressure() const;

	int getID() const { return id; }

	bool isIsolated() const { return normal == Geom::Vector3d(0.0f, 0.0f, 0.0f); }

	void setParent(PhysicsObject* object) { parent = object; }

	PhysicsObject* getParent() const { return parent; }

public:
	Geom::Vector3d center;
	Geom::Vector3d velocity;
	Geom::Vector3d force;
	Geom::Vector3d normal;
	float density;

private:
	float radius;
	const int id;
	PhysicsObject* parent;
	const float mass;

	ParticleFactory* particleFactory;

	friend class ParticleFactory;
};

typedef std::vector<Particle*> ParticleVector;
	
	}
}

#endif