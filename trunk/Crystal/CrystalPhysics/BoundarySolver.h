#ifndef __BOUNDARY_SOLVER_H__
#define __BOUNDARY_SOLVER_H__

#include "../CrystalGeom/Vector3d.h"
#include "../CrystalGeom/Box.h"
#include "PhysicsObject.h"
#include "ParticlePair.h"
#include "SPHPairSolver.h"
#include "SimulationSetting.h"

#include <vector>

#ifdef _OPENMP
#include <omp.h>
#endif

namespace Crystal{
	namespace Physics{

class BoundarySolver
{
public:

	BoundarySolver(PhysicsObject* object, const SimulationSetting& setting)
		: object( object),
		virtualParticle( object->getParticleFactory()->getVirtualParticle()),
		setting( setting)
	{}

	~BoundarySolver(void){};

	void calculateDensity(const Geom::Box& box)
	{
		const float effectLength = setting.getEffectLength();
	
		const ParticleVector& particles = object->getParticles();
		#pragma omp parallel for
		for( int i = 0; i < (int)particles.size(); ++i ) {
			Particle* particle = particles[i];
			if( particle->center.getX() > box.getMaxX() + particle->getRadius() - effectLength ) {
				Geom::Vector3d boundaryPoint = particle->center;
				boundaryPoint.setX( box.getMaxX() + particle->getRadius() );
				calculateDensity( particle, boundaryPoint ); 
			}
			else if( particle->center.getX() < box.getMinX() -particle->getRadius() + effectLength ) {
				Geom::Vector3d boundaryPoint = particle->center;
				boundaryPoint.setX( box.getMinX() - particle->getRadius() );
				calculateDensity( particle, boundaryPoint );
			}

			if( particle->center.getY() > box.getMaxY() + particle->getRadius() - effectLength ) {
				Geom::Vector3d boundaryPoint = particle->center;
				boundaryPoint.setY( box.getMaxY() + particle->getRadius() );
				calculateDensity( particle, boundaryPoint );
			}
			else if( particle->center.getY() < box.getMinY() - particle->getRadius() + effectLength ) {
				Geom::Vector3d boundaryPoint = particle->center;
				boundaryPoint.setY( box.getMinY() - particle->getRadius() );
				calculateDensity( particle, boundaryPoint );
			}

			if( particle->center.getZ() > box.getMaxZ() + particle->getRadius() - effectLength ) {
				Geom::Vector3d boundaryPoint = particle->center;
				boundaryPoint.setZ( box.getMaxZ() + particle->getRadius() );
				calculateDensity( particle, boundaryPoint );
			}
			else if( particle->center.getZ() < box.getMinZ() -particle->getRadius() + effectLength ) {
				Geom::Vector3d boundaryPoint = particle->center;
				boundaryPoint.setZ( box.getMinZ() - particle->getRadius() );
				calculateDensity( particle, boundaryPoint );
			}
		}
	}

	void calculateForce(const Geom::Box& box)
	{
		if( object->getParticles().empty() ) {
			return;
		}

		const float timeStep = setting.timeStep;
		const Geom::Box& innerBox = box.getInnerOffset( object->getParticles().front()->getRadius() );

		const ParticleVector& particles = object->getParticles();
		#pragma omp parallel for
		for( int i = 0; i < (int)particles.size(); ++i ) {
			Particle* particle = particles[i];

			if( particle->center.getX() > innerBox.getMaxX() ) {
				const float over = particle->center.getX() - innerBox.getMaxX();
				const float force = over * particle->density / timeStep / timeStep; 
				particle->force -= Geom::Vector3d( force, 0.0, 0.0 );
			}
			else if( particle->center.getX() < innerBox.getMinX() ) {
				const float over = particle->center.getX() - innerBox.getMinX();
				const float force = over * particle->density / timeStep / timeStep;
				particle->force -= Geom::Vector3d( force, 0.0, 0.0 );
			}

			if( particle->center.getY() > innerBox.getMaxY() ) {
				const float over = particle->center.getY() - innerBox.getMaxY();
				const float force = over * particle->density / timeStep / timeStep;
				particle->force -= Geom::Vector3d( 0.0, force, 0.0 );
			}
			else if( particle->center.getY() < innerBox.getMinY() ) {
				const float over = particle->center.getY() - innerBox.getMinY();
				const float force = over * particle->density / timeStep / timeStep;
				particle->force -= Geom::Vector3d( 0.0, force, 0.0 );
			}

			if( particle->center.getZ() > innerBox.getMaxZ() ) {
				const float over = particle->center.getZ() - innerBox.getMaxZ();
				const float force = over * particle->density / timeStep / timeStep;
				particle->force -= Geom::Vector3d( 0.0, 0.0, force );
			}
			else if( particle->center.getZ() < innerBox.getMinZ() ) {
				const float over = particle->center.getZ() - innerBox.getMinZ();
				const float force = over * particle->density / timeStep / timeStep;
				particle->force -= Geom::Vector3d( 0.0, 0.0, force );
			}
		}
	}


private:

	void calculateDensity(Particle* particle, const Geom::Vector3d boundaryPoint)
	{
		virtualParticle->center = boundaryPoint;
		virtualParticle->setParent( particle->getParent() );
		
		ParticlePair pair( particle, virtualParticle );
		SPHPairSolver solver( setting.getEffectLength() );
		solver.calculateDensity( pair);
	}

private:
	PhysicsObject* object;
	Particle* virtualParticle;
	const SimulationSetting& setting;
};

	}
}

#endif