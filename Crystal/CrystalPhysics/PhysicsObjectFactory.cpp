
#include "PhysicsObjectFactory.h"

#include "PhysicsObject.h"
#include "Fluid.h"
#include "Rigid.h"
#include "Obstacle.h"

#include "Particle.h"
#include "ParticleFactory.h"

#include "ParticleConditions.h"

#include "EnforcerBase.h"
#include "RigidEnforcer.h"
#include "SimulationSetting.h"

#include "../CrystalGeom/Vector3d.h"
#include "../CrystalGeom/Box.h"

#include <boost/foreach.hpp>

#include <cassert>
#include <fstream>

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
	BOOST_FOREACH( PhysicsObject* object, physicsObjects ) {
		delete object->getParticleFactory();
		delete object;
	}
	physicsObjects.clear();
	this->nextID = 0;
}

void PhysicsObjectFactory::createSearchParticles(const double effectLength)
{
	searchParticleFactory = SearchParticleFactory( ParticleVector(), effectLength );
	ParticleVector particles;
	BOOST_FOREACH( PhysicsObject* object, physicsObjects ) {
		const ParticleVector& particles = object->getParticleFactory()->getParticles();
		searchParticleFactory.addParticles( particles, effectLength );
	}
}

SearchParticleVector PhysicsObjectFactory::getSearchParticles(const double effectLength)
{
	searchParticleFactory = SearchParticleFactory( getSortedParticles(), effectLength );
	return searchParticleFactory.getSearchParticles();
}

PhysicsObject* PhysicsObjectFactory::createPhysicsObject(const PhysicsObjectCondition &condition, const SimulationSetting& setting)
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
			object = new Rigid( nextID++, condition.density, condition.pressureCoefficient, condition.viscosityCoefficient, particleFactory, new RigidEnforcer() );
			break;
		case PhysicsObjectCondition::Obstacle:
			object = new Obstacle( nextID++, condition.density, condition.pressureCoefficient, condition.viscosityCoefficient, particleFactory, new EnforcerBase() );
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

void PhysicsObjectFactory::writeToFile(const std::string& fileName) const
{
	std::ofstream ofs( fileName.c_str() ) ;
	const ParticleVector& particles = getSortedParticles();
	ofs << particles.size() << std::endl;
	BOOST_FOREACH( Particle* particle, particles ){
		ofs << particle->getParent()->getID() << "," << particle->getID() <<  "," << particle->center.getX() << "," << particle->center.getY() << "," << particle->center.getZ() << std::endl;
	}
}

ParticleVector PhysicsObjectFactory::getOrderedParticles() const
{
	ParticleVector ordered;
	BOOST_FOREACH( PhysicsObject* object, physicsObjects ) {
		const ParticleVector& particles = object->getParticles();
		ordered.insert( ordered.end(), particles.begin(), particles.end() );
	}
	return ordered;
}