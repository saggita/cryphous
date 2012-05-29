#include "Particle.h"

#include "PhysicsObject.h"

#include "ParticleFactory.h"

#include "ParticleDerive.h"

#include "../CrystalGeom/Point3d.h"
#include "../CrystalGeom/Vector3d.h"

#include <cassert>

using namespace Crystal::Geom;
using namespace Crystal::Physics;

Particle::Particle(int id, const Point3d& center, const double mass, const double radius, ParticleFactory* particleFactory) :
id( id),
center( center),
mass( mass),
velocity( Vector3d()),
radius( radius ),
density( 0.0 ),
parent( 0 ),
particleFactory( particleFactory),
derive( new ParticleDerive() )
{
}

Particle::~Particle(void)
{
	delete derive;
}

Particle* Particle::createClone(const int id) const
{
	Particle* particle = new Particle( id, center, getMass(), getRadius(), particleFactory );
	return particle;
}

void Particle::resetDiffParameters(){
	this->getDensity() = 0.0;
	this->derive->init();
}

double Particle::getPressure() const
{
	return parent->getGasConstant() * ( std::pow( density / parent->getDensity(), 1 ) - 1.0 );
}

double Particle::getIdealVolume() const
{
	return std::pow( getRadius() * 2.0, 2 );
}