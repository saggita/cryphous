#include "PhysicsObject.h"

#include "PhysicsObjectFactory.h"

#include "Particle.h"

#include "EnforcerBase.h"

#include "../CrystalGeom/Vector3d.h"

#include <boost/foreach.hpp>
#include <cassert>

using namespace Crystal::Geom;
using namespace Crystal::Physics;

PhysicsObject::PhysicsObject(const int id, const double density, const double gasConstant, const double viscosityCoefficient,
							 ParticleFactory* particleFactory,
							 EnforcerBase* enforcerBase) :
id( id),
density( density),
gasConstant( gasConstant),
viscosityCoefficient( viscosityCoefficient),
particleFactory( particleFactory),
enforcerBase( enforcerBase)
{
}

PhysicsObject::~PhysicsObject(void)
{
	delete enforcerBase;
}

void PhysicsObject::enforce(const double proceedTime)
{
	enforcerBase->enforce( this, proceedTime );
}

Vector3d PhysicsObject::getCenter() const
{
	if( getParticles().empty() ) {
		return Vector3d( 0.0, 0.0, 0.0);
	}

	/// ‘S—±Žq‚Í“¯ˆêŽ¿—Ê‚Æ‰¼’è.
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

double PhysicsObject::getWeight() const
{
	double weight = 0.0;
	BOOST_FOREACH(Particle* particle, getParticles()) {
		weight += particle->getMass();
	}
	return weight;
}