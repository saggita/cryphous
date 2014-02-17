#include "SPHSolver.h"

#include "NeighborSearcher.h"

#include "Coordinator.h"

#include <algorithm>

using namespace Crystal::Math;
using namespace Crystal::Physics;

#ifdef _OPENMP
#include <omp.h>
#endif

float getPoly6Kernel( const float distance, const float effectLength )
{
	const float poly6Constant = 315.0f / (64.0f * Tolerances::getPI() * pow( effectLength,9 ) );
	return poly6Constant * pow( effectLength * effectLength - distance * distance, 3 );
}

Vector3d getPoly6KernelGradient( const Vector3d& distanceVector, const float effectLength )
{
	const float distance = distanceVector.getLength();
	const float poly6ConstantGradient = 945.0f / ( 32.0f * Tolerances::getPI() * pow( effectLength,9 ) );
	const float factor = poly6ConstantGradient * pow( effectLength * effectLength - distance * distance, 2 );
	return distanceVector * factor;
}

float getPoly6KernelLaplacian(const float distance, const float effectLength )
{
	const float poly6ConstantLaplacian = 945.0f / ( 32.0f * Tolerances::getPI() * pow(effectLength,9 ) );
	return poly6ConstantLaplacian * ( effectLength * effectLength - distance * distance ) 
		* ( 42.0f * distance * distance - 18.0f * effectLength * effectLength );
}

Vector3d getSpikyKernelGradient(const Vector3d &distanceVector, const float effectLength )
{
	const float constant = 45.0f / ( Tolerances::getPI() * pow(effectLength, 6 ) );
	const float distance = distanceVector.getLength();
	return distanceVector * constant * pow ( effectLength - distance, 2 ) / distance;
}

float getViscosityKernelLaplacian(const float distance, const float effectLength )
{
	const float constant = 45.0f / ( Tolerances::getPI() * pow(effectLength, 6) );
	return (effectLength - distance ) * constant;
}

void SPHSolver::solve( const ParticleVector& particles, const float effectLength )
{	
	if( particles.empty() ) {
		return;
	}

	for( Particle* particle : particles ) {
		particle->init();
	}

	const ParticlePairVector& pairs = NeighborSearcher::createPairs( particles, effectLength );
		
	#pragma omp parallel for
	for( int i = 0; i < static_cast<int>( pairs.size() ); ++i ) {
		const float distance = pairs[i].getDistance();
		pairs[i].particle1->addDensity( getPoly6Kernel( distance, effectLength ) * pairs[i].particle2->getMass() );
	}
	
	for( int i = 0; i < static_cast<int>( particles.size() ); ++i ) {
		particles[i]->addDensity( getPoly6Kernel( 0.0, effectLength ) * particles[i]->getMass() );
	}

	#pragma omp parallel for
	for( int i = 0; i < static_cast<int>( pairs.size() ); ++i ) {
		const float pressure = pairs[i].getPressure();
		const Vector3d distanceVector = pairs[i].getDistanceVector();
		pairs[i].particle1->addForce( ::getSpikyKernelGradient( distanceVector, effectLength ) * pressure * pairs[i].particle2->getVolume() );

		const float viscosityCoe = pairs[i].getViscosityCoe();
		const Vector3d velocityDiff = pairs[i].getVelocityDiff();
		const float distance = pairs[i].getDistance();
		pairs[i].particle1->addForce( viscosityCoe * velocityDiff * ::getViscosityKernelLaplacian( distance, effectLength ) * pairs[i].particle2->getVolume() );
	}
}

void SPHSolver::init() { 
	step = 0;
	simulationTime = 0.0;
};

void SPHSolver::simulate(const PhysicsObjectCollection& objects, const float effectLength, const float timeStep)
{
	solve( objects.getParticles(), effectLength );

	objects.coordinate( timeStep );

	++step;
	simulationTime += timeStep;
}