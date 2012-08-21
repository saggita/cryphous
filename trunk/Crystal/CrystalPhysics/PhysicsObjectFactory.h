#ifndef __PHYSICS_OBJECT_FACTORY_H__
#define __PHYSICS_OBJECT_FACTORY_H__

#include <boost/noncopyable.hpp>
#include <list>

#include "SearchParticleFactory.h"
#include "PhysicsObject.h"
#include "ParticleConditions.h"
#include "Particle.h"
#include "Fluid.h"
#include "Rigid.h"
#include "Obstacle.h"

namespace Crystal{
	namespace Physics{
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
	PhysicsObjectFactory() :nextID( 0)
	{
	}

	~PhysicsObjectFactory(void)
	{
		init();
	}

	void init()
	{
		BOOST_FOREACH( PhysicsObject* object, physicsObjects ) {
			delete object->getParticleFactory();
			delete object;
		}
		physicsObjects.clear();
		this->nextID = 0;
	}


	PhysicsObject* createPhysicsObject( const PhysicsObjectCondition& condition, const SimulationSetting& setting )
	{
		const ParticleConditions particleCondition( condition.points, setting.particleDiameter, condition.density);
		ParticleFactory* particleFactory = new ParticleFactory();

		ParticleVector& particles = particleFactory->createParticles( particleCondition );
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
			default:
				assert( false );
		}

		BOOST_FOREACH( Particle* particle, particles ) {
			particle->setParent( object );
		}
		physicsObjects.push_back( object );
		createSearchParticles( setting.getEffectLength() );
		return object;
	}

	PhysicsObjectList getPhysicsObjects() const { return physicsObjects; }

	SearchParticleVector getSearchParticles(const float effectLength) {
		searchParticleFactory = SearchParticleFactory( getSortedParticles(), effectLength );
		return searchParticleFactory.getSearchParticles();
	}

	ParticleVector getOrderedParticles() const
	{
		ParticleVector ordered;
		BOOST_FOREACH( PhysicsObject* object, physicsObjects ) {
			const ParticleVector& particles = object->getParticles();
			ordered.insert( ordered.end(), particles.begin(), particles.end() );
		}
		return ordered;
	}

	ParticleVector getSortedParticles() const { return searchParticleFactory.getParticles(); }

private:
	int nextID;
	PhysicsObjectList physicsObjects;
	SearchParticleFactory searchParticleFactory;

	void createSearchParticles(const float effectLength)
	{
		searchParticleFactory = SearchParticleFactory( ParticleVector(), effectLength );
		ParticleVector particles;
		BOOST_FOREACH( PhysicsObject* object, physicsObjects ) {
			const ParticleVector& particles = object->getParticleFactory()->getParticles();
			searchParticleFactory.addParticles( particles, effectLength );
		}
	}
};

	}
}

#endif