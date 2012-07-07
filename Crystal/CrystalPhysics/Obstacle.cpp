
#include "Obstacle.h"
#include "Particle.h"

using namespace Crystal::Physics;

Obstacle::Obstacle( const int id, const double density, const double gasConstant, const double viscosityCoefficient, ParticleFactory* particleFactory ) :
PhysicsObject( id , density, gasConstant, viscosityCoefficient, particleFactory )
{
}

Obstacle::~Obstacle()
{
}

