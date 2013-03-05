#include "BoundarySolver.h"

using namespace Cryphous::Geometry;
using namespace Cryphous::Physics;

#ifdef _OPENMP
#include <omp.h>
#endif

void BoundarySolver::calculateDensity(const Box& box)
{
	const float effectLength = setting.getEffectLength();
	
	const ParticleVector& particles = object->getParticles();
	#pragma omp parallel for
	for( int i = 0; i < (int)particles.size(); ++i ) {
		Particle* particle = particles[i];
		if( particle->center.x > box.maxX + particle->getRadius() - effectLength ) {
			Geometry::Vector3d boundaryPoint = particle->center;
			boundaryPoint.x = box.maxX + particle->getRadius();
			calculateDensity( particle, boundaryPoint ); 
		}
		else if( particle->center.x < box.minX -particle->getRadius() + effectLength ) {
			Geometry::Vector3d boundaryPoint = particle->center;
			boundaryPoint.x = box.minX - particle->getRadius();
			calculateDensity( particle, boundaryPoint );
		}

		if( particle->center.y > box.maxY + particle->getRadius() - effectLength ) {
			Geometry::Vector3d boundaryPoint = particle->center;
			boundaryPoint.y = box.maxY + particle->getRadius();
			calculateDensity( particle, boundaryPoint );
		}
		else if( particle->center.y < box.minY - particle->getRadius() + effectLength ) {
			Geometry::Vector3d boundaryPoint = particle->center;
			boundaryPoint.y =  box.minY - particle->getRadius();
			calculateDensity( particle, boundaryPoint );
		}

		if( particle->center.z > box.maxZ + particle->getRadius() - effectLength ) {
			Geometry::Vector3d boundaryPoint = particle->center;
			boundaryPoint.z = box.maxZ + particle->getRadius();
			calculateDensity( particle, boundaryPoint );
		}
		else if( particle->center.z < box.minZ -particle->getRadius() + effectLength ) {
			Geometry::Vector3d boundaryPoint = particle->center;
			boundaryPoint.z = box.minZ - particle->getRadius();
			calculateDensity( particle, boundaryPoint );
		}
	}
}

void BoundarySolver::calculateForce(const Box& box)
{
	if( object->getParticles().empty() ) {
		return;
	}

	const float timeStep = setting.timeStep;
	const Geometry::Box& innerBox = box.getInnerOffset( object->getParticles().front()->getRadius() );

	const ParticleVector& particles = object->getParticles();
	#pragma omp parallel for
	for( int i = 0; i < (int)particles.size(); ++i ) {
		Particle* particle = particles[i];

		if( particle->center.x > innerBox.maxX ) {
			const float over = particle->center.x - innerBox.maxX;
			const float force = over * particle->density / timeStep / timeStep; 
			particle->force -= Geometry::Vector3d( force, 0.0, 0.0 );
		}
		else if( particle->center.x < innerBox.minX ) {
			const float over = particle->center.x - innerBox.minX;
			const float force = over * particle->density / timeStep / timeStep;
			particle->force -= Geometry::Vector3d( force, 0.0, 0.0 );
		}

		if( particle->center.y > innerBox.maxY ) {
			const float over = particle->center.y - innerBox.maxY;
			const float force = over * particle->density / timeStep / timeStep;
			particle->force -= Geometry::Vector3d( 0.0, force, 0.0 );
		}
		else if( particle->center.y < innerBox.minY ) {
			const float over = particle->center.y - innerBox.minY;
			const float force = over * particle->density / timeStep / timeStep;
			particle->force -= Geometry::Vector3d( 0.0, force, 0.0 );
		}

		if( particle->center.z > innerBox.maxZ ) {
			const float over = particle->center.z - innerBox.maxZ;
			const float force = over * particle->density / timeStep / timeStep;
			particle->force -= Geometry::Vector3d( 0.0, 0.0, force );
		}
		else if( particle->center.z < innerBox.minZ ) {
			const float over = particle->center.z - innerBox.minZ;
			const float force = over * particle->density / timeStep / timeStep;
			particle->force -= Geometry::Vector3d( 0.0, 0.0, force );
		}
	}
}

void BoundarySolver::calculateDensity(Particle* particle, const Vector3d boundaryPoint)
{
	virtualParticle->center = boundaryPoint;
		
	ParticlePair pair( particle, virtualParticle );
	SPHPairSolver solver( setting.getEffectLength() );
	solver.calculateDensity( pair);
}