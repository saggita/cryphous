#include "ParticleDerive.h"

using namespace Crystal::Geom;
using namespace Crystal::Physics;

ParticleDerive::ParticleDerive(void)
{
	init();
}

void ParticleDerive::init()
{
	force = Vector3d( 0.0, 0.0, 0.0 );
	intermediateDensity = 0.0;
}