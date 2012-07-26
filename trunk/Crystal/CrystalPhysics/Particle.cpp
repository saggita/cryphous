#include "Particle.h"

#include "PhysicsObject.h"

#include "ParticleFactory.h"

#include "../CrystalGeom/Vector3d.h"
#include "../CrystalGeom/Vector3d.h"

#include <cassert>

using namespace Crystal::Geom;
using namespace Crystal::Physics;

Particle::Particle(int id, const Vector3d& center, const float mass, const float radius, ParticleFactory* particleFactory) :
id( id),
center( center),
mass( mass),
velocity( Vector3d()),
radius( radius ),
density( 0.0 ),
parent( 0 ),
particleFactory( particleFactory)
{
}

Particle::~Particle(void)
{
}

Particle* Particle::createClone(const int id) const
{
	Particle* particle = new Particle( id, center, getMass(), getRadius(), particleFactory );
	return particle;
}

void Particle::resetDiffParameters(){
	density = 0.0;
	force = Vector3d( 0.0, 0.0, 0.0);
}

float Particle::getPressure() const
{
	return parent->getGasConstant() * ( std::pow( density / parent->getDensity(), 1 ) - 1.0f );
}

float Particle::getIdealVolume() const
{
	return std::pow( getRadius() * 2.0f, 2 );
}