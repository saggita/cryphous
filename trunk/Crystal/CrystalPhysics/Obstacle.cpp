
#include "Obstacle.h"
#include "Particle.h"
#include "EnforcerBase.h"

using namespace Crystal::Physics;

Obstacle::Obstacle( const int id, const double density, const double gasConstant, const double viscosityCoefficient, 
			 ParticleFactory* particleFactory,
			 EnforcerBase* enforcerBase ) :
PhysicsObject( id , density, gasConstant, viscosityCoefficient, particleFactory, enforcerBase)
{
}

Obstacle::~Obstacle()
{
}

