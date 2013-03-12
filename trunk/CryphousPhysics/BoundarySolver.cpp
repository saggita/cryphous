#include "BoundarySolver.h"

using namespace Cryphous::Geometry;
using namespace Cryphous::Physics;

#ifdef _OPENMP
#include <omp.h>
#endif

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