
#include "Obstacle.h"
#include "Particle.h"

using namespace Crystal::Physics;

Obstacle::Obstacle( const int id, const float density, const float gasConstant, const float viscosityCoefficient, ParticleFactory* particleFactory ) :
PhysicsObject( id , density, gasConstant, viscosityCoefficient, particleFactory )
{
}

Obstacle::~Obstacle()
{
}

