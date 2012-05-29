#include "Spring.h"

#include "ParticlePair.h"
#include "Particle.h"
#include "ParticleDerive.h"

#include "../CrystalGeom/Line.h"

using namespace Crystal::Geom;
using namespace Crystal::Physics;

Line Spring::getLine() const
{
	return Line( particleX->center, particleY->center );
}

void Spring::enforce(const double restDistance, const double springCoefficient) const
{
	if( isEmpty() ) {
		return;
	}

	ParticlePair pair( particleX, particleY );

	const double distance = pair.getDistance();
	Vector3d force = springCoefficient * (restDistance - distance) * pair.getDistanceVector();

	particleX->getDerive()->force += force;
	particleY->getDerive()->force -= force;
}
