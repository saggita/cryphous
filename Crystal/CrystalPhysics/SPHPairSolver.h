#ifndef __SPH_PAIR_SOLVER_H__
#define __SPH_PAIR_SOLVER_H__

#include "../CrystalGeom/Vector3d.h"
#include "Kernels3D.h"
#include "Particle.h"
#include "ParticlePair.h"
#include "PhysicsObject.h"

namespace Crystal{
	namespace Physics {

class SPHPairSolver
{
public:
	SPHPairSolver::SPHPairSolver( const float effectLength ) :
	kernels( effectLength)
	{
	}

	SPHPairSolver::~SPHPairSolver()
	{
	}

	void calculateDensity( const ParticlePair& pair )
	{
		const float result = kernels.getPoly6Kernel( pair.getDistance() );
		pair.getParticleX()->density += result * pair.getParticleY()->getMass();
		pair.getParticleY()->density += result * pair.getParticleX()->getMass();
	}

	void calculateDensity(Particle* particle)
	{
		const float result = kernels.getPoly6Kernel( 0.0 );
		particle->density += result * particle->getMass();
	}

	void calculateBoundaryDensity( const ParticlePair& pair )
	{
		Particle* particleX = pair.getParticleX();
		Particle* particleY = pair.getParticleY();

		const float result = kernels.getPoly6Kernel( pair.getDistance() );
		particleX->density += result * particleX->getMass();
		particleY->density += result * particleY->getMass();
	}

	void calculatePressureForce( const ParticlePair& pair )
	{
		const float pressureX = pair.getParticleX()->getPressure();
		const float pressureY = pair.getParticleY()->getPressure();

		const Geom::Vector3d pressure = kernels.getSpikyKernelGradient( pair.getDistanceVector() ) *
			( pressureX + pressureY ) * 0.5f;
		pair.getParticleX()->force += pressure * pair.getParticleY()->getVolume();
		pair.getParticleY()->force -= pressure * pair.getParticleX()->getVolume();
	}

	void calculateViscosityForce( const ParticlePair& pair )
	{
		const float viscosityCoefficient = ( pair.getParticleX()->getParent()->getViscosityCoefficient() + 
			pair.getParticleY()->getParent()->getViscosityCoefficient() ) * 0.5f;
		const Geom::Vector3d diffVector( pair.getParticleX()->velocity, pair.getParticleY()->velocity );
		const Geom::Vector3d viscosity = viscosityCoefficient * diffVector * 
			kernels.getViscosityKernelLaplacian( pair.getDistance() );
		pair.getParticleX()->force += viscosity * pair.getParticleY()->getVolume();
		pair.getParticleY()->force -= viscosity * pair.getParticleX()->getVolume();
	}

	void calculateNormal( const ParticlePair& pair )
	{
		const Geom::Vector3d& kernel = kernels.getPoly6KernelGradient( pair.getDistanceVector() );
		pair.getParticleX()->normal += kernel * pair.getParticleY()->getVolume();
		pair.getParticleY()->normal -= kernel * pair.getParticleX()->getVolume();
	}

	void countNeighbors( const ParticlePair& pair )
	{
		pair.getParticleX()->neighbors++;
		pair.getParticleY()->neighbors++;
	}

private:
	Kernels3D kernels;
};

	}
}

#endif