#include "SPHPairSolver.h"

#include "Particle.h"
#include "ParticleDerive.h"

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

void SPHPairSolver::calculateIntermediateDensity( ParticlePair* pair )
{
	const double volume = pair->getParticleX()->getIdealVolume();
	const double result = volume * kernels->getPoly6Kernel( pair->getDistance() );
	pair->getParticleX()->getDerive()->intermediateDensity += result;
	pair->getParticleY()->getDerive()->intermediateDensity += result;
}

void SPHPairSolver::calculateIntermediateDensity( Particle* particle )
{
	particle->getDerive()->intermediateDensity += particle->getIdealVolume() * kernels->getPoly6Kernel( 0.0 );
}

void SPHPairSolver::calculateDensity( ParticlePair* pair )
{
	const double result = kernels->getPoly6Kernel( pair->getDistance() );
	pair->getParticleX()->getDensity() += result * pair->getParticleY()->getMass(); // / pair->getParticleY()->getDerive()->intermediateDensity;
	pair->getParticleY()->getDensity() += result * pair->getParticleX()->getMass(); // / pair->getParticleX()->getDerive()->intermediateDensity;
}

void SPHPairSolver::calculateDensity(Particle* particle)
{
	const double result = kernels->getPoly6Kernel( 0.0 );
	particle->getDensity() += result * particle->getMass(); // / particle->getDerive()->intermediateDensity;
}

void SPHPairSolver::calculateBoundaryDensity( ParticlePair* pair )
{
	Particle* particleX = pair->getParticleX();
	Particle* particleY = pair->getParticleY();

	const double result = kernels->getPoly6Kernel( pair->getDistance() );
	particleX->getDensity() += result * particleX->getMass();
	particleY->getDensity() += result * particleY->getMass();
}

void SPHPairSolver::calculatePressureForce( ParticlePair* pair )
{
	const double pressureX = pair->getParticleX()->getPressure();
	const double pressureY = pair->getParticleY()->getPressure();

	const Vector3d pressure = kernels->getSpikyKernelGradient( pair->getDistanceVector() ) *
		( pressureX + pressureY ) * 0.5;
	pair->getParticleX()->getDerive()->force += pressure * pair->getParticleY()->getVolume();
	pair->getParticleY()->getDerive()->force -= pressure * pair->getParticleX()->getVolume();
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
	pair->getParticleX()->getDerive()->force -= tension * pair->getParticleY()->getVolume();
	pair->getParticleY()->getDerive()->force += tension * pair->getParticleX()->getVolume();
}

void SPHPairSolver::calculateViscosityForce( ParticlePair* pair )
{
	const double viscosityCoefficient = ( pair->getParticleX()->getParent()->getViscosityCoefficient() + 
		pair->getParticleY()->getParent()->getViscosityCoefficient() ) * 0.5;
	const Vector3d diffVector( pair->getParticleX()->velocity, pair->getParticleY()->velocity );
	const Vector3d viscosity = viscosityCoefficient * diffVector * 
		kernels->getViscosityKernelLaplacian( pair->getDistance() );
	pair->getParticleX()->getDerive()->force += viscosity * pair->getParticleY()->getVolume();
	pair->getParticleY()->getDerive()->force -= viscosity * pair->getParticleX()->getVolume();
}