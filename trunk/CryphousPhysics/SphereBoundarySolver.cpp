#include "SphereBoundarySolver.h"

using namespace Cryphous::Geometry;
using namespace Cryphous::Physics;

#ifdef _OPENMP
#include <omp.h>
#endif

/*void SphereBoundarySolver::calculateDensity(const Sphere& sphere)
{
	if( object->getParticles().empty() ) {
		return;
	}
	const float effectLength = setting.getEffectLength();

	const ParticleVector& particles = object->getParticles();
	#pragma omp parallel for
	for( int i = 0; i < (int)particles.size(); ++i ) {
		Particle* particle = particles[i];

		if( sphere.isExterior( particle->center ) ) {
			Vector3d boundaryPoint;
			calculateDensity( particle, boundaryPoint);
		}

		/*if( particle->center.x > box.maxX + particle->getRadius() - effectLength ) {
			Geometry::Vector3d boundaryPoint = particle->center;
			boundaryPoint.x = box.maxX + particle->getRadius();
			calculateDensity( particle, boundaryPoint ); 
		}*/
//	}
//}

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

void SphereBoundarySolver::calculateDensity(Particle* particle, const Vector3d boundaryPoint)
{
	virtualParticle->center = boundaryPoint;
		
	ParticlePair pair( particle, virtualParticle );
	SPHPairSolver solver( setting.getEffectLength() );
	solver.calculateDensity( pair);
}