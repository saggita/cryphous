#include "PhysicsObject.h"

#include "PhysicsObjectFactory.h"

#include "Particle.h"

#include "../CrystalGeom/Vector3d.h"

#include <boost/foreach.hpp>
#include <cassert>

using namespace Crystal::Geom;
using namespace Crystal::Physics;

PhysicsObject::PhysicsObject(const int id, const float density, const float gasConstant, const float viscosityCoefficient,ParticleFactory* particleFactory) :
id( id),
density( density),
gasConstant( gasConstant),
viscosityCoefficient( viscosityCoefficient),
particleFactory( particleFactory)
{
}

PhysicsObject::~PhysicsObject(void)
{
}

Vector3d PhysicsObject::getCenter() const
{
	if( getParticles().empty() ) {
		return Vector3d( 0.0, 0.0, 0.0);
	}

	Vector3d center( 0.0, 0.0, 0.0);
	BOOST_FOREACH(Particle* particle, getParticles()) {
		center += particle->center;
	}
	return center /= getParticles().size();
}

Vector3d PhysicsObject::getAverageVelosity() const
{
	Vector3d averageVelosity( 0.0, 0.0, 0.0 );
	BOOST_FOREACH( Particle* particle, getParticles() ) {
		averageVelosity += particle->velocity;
	}
	return averageVelosity / getParticles().size();
}

float PhysicsObject::getWeight() const
{
	float weight = 0.0;
	BOOST_FOREACH(Particle* particle, getParticles()) {
		weight += particle->getMass();
	}
	return weight;
}