
#include "PhysicsObjectFactory.h"

#include "PhysicsObject.h"
#include "PhysicsObjectCondition.h"
#include "Fluid.h"
#include "Rigid.h"

#include "Particle.h"
#include "ParticleFactory.h"

#include "ParticleConditions.h"

#include "PhysicalTimeIntegrator.h"
#include "EnforcerBase.h"
#include "RigidEnforcer.h"

#include "../CrystalGeom/Point3d.h"
#include "../CrystalGeom/Box.h"

#include <boost/foreach.hpp>

#include <cassert>

using namespace Crystal::Geom;
using namespace Crystal::Physics;

PhysicsObjectFactory::PhysicsObjectFactory(void) :
nextID( 0)
{
}

PhysicsObjectFactory::~PhysicsObjectFactory(void)
{
	init();
}

void PhysicsObjectFactory::init()
{
	initPhysicsObjects();
	initConditions();
}

void PhysicsObjectFactory::initPhysicsObjects()
{
	BOOST_FOREACH( PhysicsObject* object, physicsObjects ) {
		delete object->getParticleFactory();
		delete object;
	}
	physicsObjects.clear();
	this->nextID = 0;
}

void PhysicsObjectFactory::initConditions()
{
	BOOST_FOREACH( PhysicsObjectCondition* condition, conditions ) {
		delete condition;
	}
	conditions.clear();
}

void PhysicsObjectFactory::reCreatePhysicsObject(const double effectLength)
{
	initPhysicsObjects();
	PhysicsObjectConditionList previousConditions = this->conditions;
	BOOST_FOREACH( PhysicsObjectCondition* condition, previousConditions ) {
		createPhysicsObject( *condition, effectLength);
		conditions.remove( condition);
		delete condition;
	}
	createSearchParticles(effectLength);
}

void PhysicsObjectFactory::createSearchParticles(const double effectLength)
{
	searchParticleFactory = SearchParticleFactory( ParticleVector(), effectLength );
	ParticleVector particles;
	BOOST_FOREACH( PhysicsObject* object, physicsObjects ) {
		const ParticleVector& particles = object->getParticleFactory()->getParticles();
		searchParticleFactory.addParticles( particles, effectLength );
	}
	//searchParticleFactory = SearchParticleFactory( getParticles(), effectLength );
}

SearchParticleVector PhysicsObjectFactory::getSearchParticles(const double effectLength)
{
	searchParticleFactory = SearchParticleFactory( getSortedParticles(), effectLength );
	return searchParticleFactory.getSearchParticles();
}

PhysicsObject* PhysicsObjectFactory::createPhysicsObject(const PhysicsObjectCondition &condition, const double effectLength)
{
	const ParticleConditions particleCondition( condition.getBox(), condition.getDivideLength(), condition.getDensity());
	ParticleFactory* particleFactory = new ParticleFactory();

	ParticleVector& particles = particleFactory->createParticles( particleCondition );
	PhysicsObject* object = 0;
	switch( condition.getObjectType() ) {
		case PhysicsObjectCondition::Fluid :
			object = new Fluid( nextID++, condition.getDensity(), condition.getPressureCoefficient(), condition.getViscosityCoefficient(), particleFactory);
			break;
		case PhysicsObjectCondition::Rigid :
			object = new Rigid( nextID++, condition.getDensity(), condition.getPressureCoefficient(), condition.getViscosityCoefficient(), particleFactory, new PhysicalTimeIntegratorBase(),
				new EnforcerBase(),
				particleCondition.getXNumber(), particleCondition.getYNumber(), particleCondition.getZNumber() );
			break;
		case PhysicsObjectCondition::RigidTwoWay:
			object = new Rigid( nextID++, condition.getDensity(), condition.getPressureCoefficient(), condition.getViscosityCoefficient(), particleFactory, new PhysicalTimeIntegrator(),
				new RigidEnforcer(),
				particleCondition.getXNumber() , particleCondition.getYNumber(), particleCondition.getZNumber() );
			break;
		default:
			assert( false );
	}

	BOOST_FOREACH( Particle* particle, particles ) {
		particle->setParent( object );
	}
	physicsObjects.push_back( object );
	conditions.push_back( new PhysicsObjectCondition( condition.getBox(), condition.getDensity(), condition.getDivideLength(),
		condition.getPressureCoefficient(), condition.getViscosityCoefficient(), condition.getObjectType() ) );
	createSearchParticles(effectLength);
	return object;
}