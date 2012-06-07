#include "SPHPairSolver.h"

#include "Particle.h"

#include "ParticlePair.h"
#include "PhysicsObject.h"
#include "Kernels3D.h"
#include "Kernels2D.h"
#include "../CrystalGeom/Point3d.h"
#include "../CrystalGeom/Vector3d.h"
#include "../CrystalGeom/Tolerances.h"

#include <cmath>
#include <cassert>

using namespace Crystal::Physics;
using namespace Crystal::Geom;

SPHPairSolver::SPHPairSolver( const double effectLength ) :
kernels( 0)
{
	this->kernels = new Kernels3D( effectLength );
}

SPHPairSolver::~SPHPairSolver()
{
	delete kernels;
}

void SPHPairSolver::calculateDensity( ParticlePair* pair )
{
	const double result = kernels->getPoly6Kernel( pair->getDistance() );
	pair->getParticleX()->density += result * pair->getParticleY()->getMass();
	pair->getParticleY()->density += result * pair->getParticleX()->getMass();
}

void SPHPairSolver::calculateDensity(Particle* particle)
{
	const double result = kernels->getPoly6Kernel( 0.0 );
	particle->density += result * particle->getMass();
}

void SPHPairSolver::calculateBoundaryDensity( ParticlePair* pair )
{
	Particle* particleX = pair->getParticleX();
	Particle* particleY = pair->getParticleY();

	const double result = kernels->getPoly6Kernel( pair->getDistance() );
	particleX->density += result * particleX->getMass();
	particleY->density += result * particleY->getMass();
}

void SPHPairSolver::calculatePressureForce( ParticlePair* pair )
{
	const double pressureX = pair->getParticleX()->getPressure();
	const double pressureY = pair->getParticleY()->getPressure();

	const Vector3d pressure = kernels->getSpikyKernelGradient( pair->getDistanceVector() ) *
		( pressureX + pressureY ) * 0.5;
	pair->getParticleX()->force += pressure * pair->getParticleY()->getVolume();
	pair->getParticleY()->force -= pressure * pair->getParticleX()->getVolume();
}

void SPHPairSolver::calculateSurfaceTension( ParticlePair* pair )
{
	Vector3d colorGradient = kernels->getPoly6KernelGradient( pair->getDistanceVector() );

	const double colorGradientAbs = colorGradient.getLength();
	if( Tolerances::isEqualAsDenominator( colorGradientAbs ) ) {
		return;
	}

	const double colorLaplacian = kernels->getPoly6KernelLaplacian( pair->getDistance() );
	const Vector3d tension = colorGradient * colorLaplacian * 1.0e-8;
	pair->getParticleX()->force -= tension * pair->getParticleY()->getVolume();
	pair->getParticleY()->force += tension * pair->getParticleX()->getVolume();
}

void SPHPairSolver::calculateViscosityForce( ParticlePair* pair )
{
	const double viscosityCoefficient = ( pair->getParticleX()->getParent()->getViscosityCoefficient() + 
		pair->getParticleY()->getParent()->getViscosityCoefficient() ) * 0.5;
	const Vector3d diffVector( pair->getParticleX()->velocity, pair->getParticleY()->velocity );
	const Vector3d viscosity = viscosityCoefficient * diffVector * 
		kernels->getViscosityKernelLaplacian( pair->getDistance() );
	pair->getParticleX()->force += viscosity * pair->getParticleY()->getVolume();
	pair->getParticleY()->force -= viscosity * pair->getParticleX()->getVolume();
}