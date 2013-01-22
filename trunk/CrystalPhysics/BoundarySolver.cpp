#include "BoundarySolver.h"

using namespace Crystal::Geom;
using namespace Crystal::Physics;

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
			if( particle->center.x > box.getMaxX() + particle->getRadius() - effectLength ) {
				Geom::Vector3d boundaryPoint = particle->center;
				boundaryPoint.x = box.getMaxX() + particle->getRadius();
				calculateDensity( particle, boundaryPoint ); 
			}
			else if( particle->center.x < box.getMinX() -particle->getRadius() + effectLength ) {
				Geom::Vector3d boundaryPoint = particle->center;
				boundaryPoint.x = box.getMinX() - particle->getRadius();
				calculateDensity( particle, boundaryPoint );
			}

			if( particle->center.y > box.getMaxY() + particle->getRadius() - effectLength ) {
				Geom::Vector3d boundaryPoint = particle->center;
				boundaryPoint.y = box.getMaxY() + particle->getRadius();
				calculateDensity( particle, boundaryPoint );
			}
			else if( particle->center.y < box.getMinY() - particle->getRadius() + effectLength ) {
				Geom::Vector3d boundaryPoint = particle->center;
				boundaryPoint.y =  box.getMinY() - particle->getRadius();
				calculateDensity( particle, boundaryPoint );
			}

			if( particle->center.z > box.getMaxZ() + particle->getRadius() - effectLength ) {
				Geom::Vector3d boundaryPoint = particle->center;
				boundaryPoint.z = box.getMaxZ() + particle->getRadius();
				calculateDensity( particle, boundaryPoint );
			}
			else if( particle->center.z < box.getMinZ() -particle->getRadius() + effectLength ) {
				Geom::Vector3d boundaryPoint = particle->center;
				boundaryPoint.z = box.getMinZ() - particle->getRadius();
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
		const Geom::Box& innerBox = box.getInnerOffset( object->getParticles().front()->getRadius() );

		const ParticleVector& particles = object->getParticles();
		#pragma omp parallel for
		for( int i = 0; i < (int)particles.size(); ++i ) {
			Particle* particle = particles[i];

			if( particle->center.x > innerBox.getMaxX() ) {
				const float over = particle->center.x - innerBox.getMaxX();
				const float force = over * particle->density / timeStep / timeStep; 
				particle->force -= Geom::Vector3d( force, 0.0, 0.0 );
			}
			else if( particle->center.x < innerBox.getMinX() ) {
				const float over = particle->center.x - innerBox.getMinX();
				const float force = over * particle->density / timeStep / timeStep;
				particle->force -= Geom::Vector3d( force, 0.0, 0.0 );
			}

			if( particle->center.y > innerBox.getMaxY() ) {
				const float over = particle->center.y - innerBox.getMaxY();
				const float force = over * particle->density / timeStep / timeStep;
				particle->force -= Geom::Vector3d( 0.0, force, 0.0 );
			}
			else if( particle->center.y < innerBox.getMinY() ) {
				const float over = particle->center.y - innerBox.getMinY();
				const float force = over * particle->density / timeStep / timeStep;
				particle->force -= Geom::Vector3d( 0.0, force, 0.0 );
			}

			if( particle->center.z > innerBox.getMaxZ() ) {
				const float over = particle->center.z - innerBox.getMaxZ();
				const float force = over * particle->density / timeStep / timeStep;
				particle->force -= Geom::Vector3d( 0.0, 0.0, force );
			}
			else if( particle->center.z < innerBox.getMinZ() ) {
				const float over = particle->center.z - innerBox.getMinZ();
				const float force = over * particle->density / timeStep / timeStep;
				particle->force -= Geom::Vector3d( 0.0, 0.0, force );
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