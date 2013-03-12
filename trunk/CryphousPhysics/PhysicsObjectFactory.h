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

	void init()
	{
		for( PhysicsObjectVector::const_iterator iter = physicsObjects.begin(); iter != physicsObjects.end(); ++iter ) {
			delete (*iter)->getParticleFactory();
			delete (*iter);
		}
		physicsObjects.clear();
		this->nextID = 0;
	}


	PhysicsObject* createPhysicsObject( const PhysicsObjectCondition& condition, const SimulationSetting& setting )
	{
		const ParticleConditions particleCondition( setting.particleDiameter, condition.density, condition.pressureCoefficient, condition.viscosityCoefficient);
		ParticleFactory* particleFactory = new ParticleFactory();

		ParticleVector& particles = particleFactory->createParticles( condition.points, particleCondition );
		PhysicsObject* object = 0;
		switch( condition.objectType ) {
			case PhysicsObjectCondition::Fluid :
				object = new Fluid( nextID++, condition.density, condition.pressureCoefficient, condition.viscosityCoefficient, particleFactory);
				break;
			case PhysicsObjectCondition::Rigid :
				object = new Rigid( nextID++, condition.density, condition.pressureCoefficient, condition.viscosityCoefficient, particleFactory );
				break;
			case PhysicsObjectCondition::Obstacle:
				object = new Obstacle( nextID++, condition.density, condition.pressureCoefficient, condition.viscosityCoefficient, particleFactory );
				break;
			case PhysicsObjectCondition::Elastic:
				object = new Elastic( nextID++, condition.density, condition.pressureCoefficient, condition.viscosityCoefficient, particleFactory );
				break;
			default:
				assert( false );
		}

		physicsObjects.push_back( object );
		return object;
	}

	/*PhysicsObject* addParticles( const int index, const std::vector<Geometry::Vector3d>& points, const std::vector<Geometry::Vector3d>& velocities )
	{
		physicsObjects[index]->getParticleFactory()->addParticles( points, velocities );
		return physicsObjects[index];
	}*/

	PhysicsObjectVector getPhysicsObjects() const { return physicsObjects; }

	ParticleVector getParticles() const
	{
		ParticleVector ordered;
		for( PhysicsObjectVector::const_iterator iter = physicsObjects.begin(); iter != physicsObjects.end(); ++iter ) {
			const ParticleVector& particles = (*iter)->getParticles();
			ordered.insert( ordered.end(), particles.begin(), particles.end() );
		}
		return ordered;
	}

	void exportParticles(const std::string& fileName) const
	{
		std::ofstream ofs(fileName);
		const ParticleVector& particles = getParticles();
		for( Particle* particle: particles ) {
			ofs << particle->center.x << "," << particle->center.y << "," << particle->center.z << "," << particle->density << "," << std::endl;
		}
	}

private:
	int nextID;
	PhysicsObjectVector physicsObjects;

};

	}
}

#endif