#ifndef __PHYSICS_OBJECT_FACTORY_H__
#define __PHYSICS_OBJECT_FACTORY_H__

#include <boost/noncopyable.hpp>
#include <list>

#include "SearchParticleFactory.h"

namespace Crystal{
	namespace Physics{

		class PhysicsObject;
		typedef std::list<PhysicsObject*> PhysicsObjectList;
		class Particle;
		typedef std::vector<Particle*> ParticleVector;
		class ParticleFactory;
		class SimulationSetting;

struct PhysicsObjectCondition
{
	enum ObjectType{
		Fluid,
		Rigid,
		Obstacle,
	};

	PhysicsObjectCondition( const std::vector<Geom::Vector3d>& points, const float density, const float pressureCoefficient, const float viscosityCoefficient, const ObjectType objectType) :
		points( points), 
			density( density),
			pressureCoefficient( pressureCoefficient),
			viscosityCoefficient( viscosityCoefficient),
			objectType( objectType)
		{
		}

	const std::vector<Geom::Vector3d> points;
	float density;
	float pressureCoefficient;
	float viscosityCoefficient;
	ObjectType objectType;
};

class PhysicsObjectFactory : private boost::noncopyable
{
public:
	PhysicsObjectFactory();

	~PhysicsObjectFactory(void);

	void init();

	PhysicsObject* createPhysicsObject( const PhysicsObjectCondition& condition, const SimulationSetting& setting );

	PhysicsObjectList getPhysicsObjects() const { return physicsObjects; }

	SearchParticleVector getSearchParticles(const float effectLength);

	ParticleVector getOrderedParticles() const;

	ParticleVector getSortedParticles() const { return searchParticleFactory.getParticles(); }

	void writeToFile(const std::string& fileName) const;

private:
	int nextID;
	PhysicsObjectList physicsObjects;
	SearchParticleFactory searchParticleFactory;

	void createSearchParticles(const float effectLength);
};

	}
}

#endif