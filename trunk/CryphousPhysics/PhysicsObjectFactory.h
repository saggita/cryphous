#ifndef __CRYPHOUS_PHYSICS_OBJECT_FACTORY_H__
#define __CRYPHOUS_PHYSICS_OBJECT_FACTORY_H__

#include "Uncopyable.h"
#include <vector>
#include <fstream>

#include "SimulationSetting.h"
#include "PhysicsObject.h"
#include "ParticleConditions.h"
#include "Particle.h"
#include "Fluid.h"
#include "Rigid.h"
#include "Obstacle.h"
#include "Elastic.h"

namespace Cryphous{
	namespace Physics{
		class ParticleFactory;
		class SimulationSetting;

struct PhysicsObjectCondition
{
	enum ObjectType{
		Fluid,
		Rigid,
		Obstacle,
		Elastic,
	};

	PhysicsObjectCondition( const std::vector<Geometry::Vector3d>& points, const float density, const float pressureCoefficient, const float viscosityCoefficient, const ObjectType objectType) :
		points( points), 
			density( density),
			pressureCoefficient( pressureCoefficient),
			viscosityCoefficient( viscosityCoefficient),
			objectType( objectType)
		{
		}

	const std::vector<Geometry::Vector3d> points;
	float density;
	float pressureCoefficient;
	float viscosityCoefficient;
	ObjectType objectType;
};

class PhysicsObjectFactory : private Uncopyable
{
public:
	PhysicsObjectFactory() :nextID( 0)
	{
	}

	~PhysicsObjectFactory(void)
	{
		init();
	}

	void init();

	PhysicsObject* createPhysicsObject( const PhysicsObjectCondition& condition, const SimulationSetting& setting );
	
	//PhysicsObject* addParticles( const int index, const std::vector<Geometry::Vector3d>& points, const std::vector<Geometry::Vector3d>& velocities )

	PhysicsObjectVector getPhysicsObjects() const { return physicsObjects; }

	ParticleVector getParticles() const;

private:
	int nextID;
	PhysicsObjectVector physicsObjects;

};

	}
}

#endif