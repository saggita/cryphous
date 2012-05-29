#include "PhysicsObject.h"

#include "PhysicsObjectFactory.h"

#include "Particle.h"

#include "PhysicalTimeIntegratorBase.h"
#include "EnforcerBase.h"

#include "../CrystalGeom/Point3d.h"

#include <boost/foreach.hpp>
#include <cassert>

using namespace Crystal::Geom;
using namespace Crystal::Physics;

PhysicsObject::PhysicsObject(const int id, const double density, const double gasConstant, const double viscosityCoefficient,
							 ParticleFactory* particleFactory,
							 PhysicalTimeIntegratorBase* physicalTimeIntegratorBase,
							 EnforcerBase* enforcerBase) :
id( id),
density( density),
gasConstant( gasConstant),
viscosityCoefficient( viscosityCoefficient),
particleFactory( particleFactory),
physicalTimeIntegratorBase( physicalTimeIntegratorBase),
enforcerBase( enforcerBase)
{
}

PhysicsObject::~PhysicsObject(void)
{
	delete enforcerBase;
	delete physicalTimeIntegratorBase;
}

void PhysicsObject::enforce(const double proceedTime)
{
	enforcerBase->enforce( this, proceedTime );
}

Point3d PhysicsObject::getCenter() const
{
	if( getParticles().empty() ) {
		return Point3d( 0.0, 0.0, 0.0);
	}

	/// ‘S—±Žq‚Í“¯ˆêŽ¿—Ê‚Æ‰¼’è.
	Point3d center( 0.0, 0.0, 0.0);
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

void PhysicsObject::integrateTime(const double proceedTime)
{
	physicalTimeIntegratorBase->integrateTime( *this, proceedTime );
}