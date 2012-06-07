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
		class PhysicsObjectCondition;
		typedef std::list<PhysicsObjectCondition*> PhysicsObjectConditionList;
		class ParticleFactory;

class PhysicsObjectFactory : private boost::noncopyable
{
public:
	PhysicsObjectFactory();

	~PhysicsObjectFactory(void);

	void init();

	void initPhysicsObjects();

	void initConditions();

	void reCreatePhysicsObject(const double effectLength);

	PhysicsObject* createPhysicsObject( const PhysicsObjectCondition& condition, const double effectLength );

	PhysicsObjectList getPhysicsObjects() const { return physicsObjects; }

	PhysicsObjectConditionList getConditions() const { return conditions; }

	SearchParticleVector getSearchParticles(const double effectLength);

	ParticleVector getSortedParticles() const { return searchParticleFactory.getParticles(); }

	void writeToFile(const std::string& fileName) const;

private:
	int nextID;
	PhysicsObjectList physicsObjects;
	PhysicsObjectConditionList conditions;
	SearchParticleFactory searchParticleFactory;
	std::vector<Crystal::Geom::Point3d> preparePoints;

	void createSearchParticles(const double effectLength);
};

	}
}

#endif