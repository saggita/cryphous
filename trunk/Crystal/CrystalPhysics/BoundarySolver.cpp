#include "BoundarySolver.h"

#include "../CrystalGeom/Vector3d.h"
#include "../CrystalGeom/Vector3d.h"
#include "../CrystalGeom/Box.h"

#include "Particle.h"
#include "ParticlePair.h"
#include "PhysicsObject.h"
#include "SPHPairSolver.h"
#include "SimulationSetting.h"

#include <cmath>
#include <cassert>
#include <boost/foreach.hpp>

using namespace Crystal::Geom;
using namespace Crystal::Physics;

BoundarySolver::BoundarySolver(PhysicsObject* object, const SimulationSetting& setting)
: object( object),
virtualParticle( object->getParticleFactory()->getVirtualParticle()),
setting( setting)
{
}

void BoundarySolver::calculateDensity(const Box& box)
{
	const double effectLength = setting.getEffectLength();
	BOOST_FOREACH( Particle* particle, object->getParticles() ) {
		if( particle->center.getX() > box.getMaxX() + particle->getRadius() - effectLength ) {
			Vector3d boundaryPoint = particle->center;
			boundaryPoint.setX( box.getMaxX() + particle->getRadius() );
			calculateDensity( particle, boundaryPoint ); 
		}
		else if( particle->center.getX() < box.getMinX() -particle->getRadius() + effectLength ) {
			Vector3d boundaryPoint = particle->center;
			boundaryPoint.setX( box.getMinX() - particle->getRadius() );
			calculateDensity( particle, boundaryPoint );
		}

		if( particle->center.getY() > box.getMaxY() + particle->getRadius() - effectLength ) {
			Vector3d boundaryPoint = particle->center;
			boundaryPoint.setY( box.getMaxY() + particle->getRadius() );
			calculateDensity( particle, boundaryPoint );
		}
		else if( particle->center.getY() < box.getMinY() - particle->getRadius() + effectLength ) {
			Vector3d boundaryPoint = particle->center;
			boundaryPoint.setY( box.getMinY() - particle->getRadius() );
			calculateDensity( particle, boundaryPoint );
		}

		if( particle->center.getZ() > box.getMaxZ() + particle->getRadius() - effectLength ) {
			Vector3d boundaryPoint = particle->center;
			boundaryPoint.setZ( box.getMaxZ() + particle->getRadius() );
			calculateDensity( particle, boundaryPoint );
		}
		else if( particle->center.getZ() < box.getMinZ() -particle->getRadius() + effectLength ) {
			Vector3d boundaryPoint = particle->center;
			boundaryPoint.setZ( box.getMinZ() - particle->getRadius() );
			calculateDensity( particle, boundaryPoint );
		}
	}
}

void BoundarySolver::calculateForce(const Box& box)
{
	if( object->getParticles().empty() ) {
		return;
	}

	const double timeStep = setting.timeStep;
	const Box& innerBox = box.getInnerOffset( object->getParticles().front()->getRadius() );

	BOOST_FOREACH( Particle* particle, object->getParticles() ) {

		if( particle->center.getX() > innerBox.getMaxX() ) {
			const double over = particle->center.getX() - innerBox.getMaxX();
			const double force = over * particle->density / timeStep / timeStep; 
			particle->force -= Vector3d( force, 0.0, 0.0 );
		}
		else if( particle->center.getX() < innerBox.getMinX() ) {
			const double over = particle->center.getX() - innerBox.getMinX();
			const double force = over * particle->density / timeStep / timeStep;
			particle->force -= Vector3d( force, 0.0, 0.0 );
		}

		if( particle->center.getY() > innerBox.getMaxY() ) {
			const double over = particle->center.getY() - innerBox.getMaxY();
			const double force = over * particle->density / timeStep / timeStep;
			particle->force -= Vector3d( 0.0, force, 0.0 );
		}
		else if( particle->center.getY() < innerBox.getMinY() ) {
			const double over = particle->center.getY() - innerBox.getMinY();
			const double force = over * particle->density / timeStep / timeStep;
			particle->force -= Vector3d( 0.0, force, 0.0 );
		}

		if( particle->center.getZ() > innerBox.getMaxZ() ) {
			const double over = particle->center.getZ() - innerBox.getMaxZ();
			const double force = over * particle->density / timeStep / timeStep;
			particle->force -= Vector3d( 0.0, 0.0, force );
		}
		else if( particle->center.getZ() < innerBox.getMinZ() ) {
			const double over = particle->center.getZ() - innerBox.getMinZ();
			const double force = over * particle->density / timeStep / timeStep;
			particle->force -= Vector3d( 0.0, 0.0, force );
		}
	}
}

void BoundarySolver::calculateDensity(Particle* particle, const Vector3d boundaryPoint)
{
	virtualParticle->center = boundaryPoint;
	virtualParticle->setParent( particle->getParent() );

	ParticlePair pair( particle, virtualParticle );
	SPHPairSolver solver( setting.getEffectLength() );
	solver.calculateDensity( pair);
}

BoundarySolver::~BoundarySolver(void)
{
}
