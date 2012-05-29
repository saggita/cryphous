#pragma once

#include "../CrystalGeom/Vector3d.h"

namespace Crystal{
	namespace Physics{

class ParticleDerive
{
public:
	ParticleDerive(void);

	~ParticleDerive(void){};

	void init();

	Geom::Vector3d force;
	double intermediateDensity;
};
	}
}
