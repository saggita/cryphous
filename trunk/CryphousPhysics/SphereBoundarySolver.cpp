#include "SphereBoundarySolver.h"

using namespace Cryphous::Geometry;
using namespace Cryphous::Physics;

#ifdef _OPENMP
#include <omp.h>
#endif

void SphereBoundarySolver::calculateForce(const Sphere& sphere)
{
	if( object->getParticles().empty() ) {
		return;
	}

	const float timeStep = setting.timeStep;
	const Sphere& innerSphere = sphere.getInnerOffset( object->getParticles().front()->getRadius() );

	const ParticleVector& particles = object->getParticles();
	#pragma omp parallel for
	for( int i = 0; i < (int)particles.size(); ++i ) {
		Particle* particle = particles[i];
		if( innerSphere.isExterior( particle->center ) ) {
			const Vector3d distVector = particle->center - innerSphere.center;
			const float over = innerSphere.center.getDistance( particle->center ) - innerSphere.radius;
			const float force = over * particle->density / timeStep / timeStep * 0.1;
			particle->force -= distVector * force;
		}
	}
}