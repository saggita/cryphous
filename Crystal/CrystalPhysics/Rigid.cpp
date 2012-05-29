
#include "Rigid.h"
#include "Particle.h"
#include "PhysicalTimeIntegratorBase.h"
#include "EnforcerBase.h"
#include "SpringParticleFactory.h"

#include <boost/foreach.hpp>

using namespace Crystal::Physics;

Rigid::Rigid( const int id, const double density, const double gasConstant, const double viscosityCoefficient, 
			 ParticleFactory* particleFactory,
			 PhysicalTimeIntegratorBase* physicalTimeIntegratorBase,
			 EnforcerBase* enforcerBase,
			 const int xNumber, const int yNumber, const int zNumber ) :
PhysicsObject( id , density, gasConstant, viscosityCoefficient, particleFactory, physicalTimeIntegratorBase, enforcerBase)
{
	springParticleFactory = new SpringParticleFactory( particleFactory->getParticles(), xNumber, yNumber, zNumber );
}

Rigid::~Rigid()
{
	delete springParticleFactory;
}

ParticleGrid Rigid::getParticleGrid() const
{
	return springParticleFactory->getParticleGrid();
}