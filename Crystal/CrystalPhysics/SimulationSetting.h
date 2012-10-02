#ifndef __SIMULATION_SETTING_H__
#define __SIMULATION_SETTING_H__

#include "../CrystalGeom/Vector3d.h"
#include "../CrystalGeom/Box.h"

#include "Uncopyable.h"

namespace Crystal{
	namespace Physics{

class SimulationSetting : private Uncopyable
{
public:
	SimulationSetting(void) :
	  timeStep( 0.025f ),
	  particleDiameter(0.5f),
	  boundaryBox( Geom::Vector3d(-10.0f, 0.0f, -10.0f), Geom::Vector3d(10.0f, 100.0f, 10.0f) ),
	  externalForce( Geom::Vector3d( 0.0f, -9.8f, 0.0f ) )
	  {};

	~SimulationSetting(){};

	float getEffectLength() const { return particleDiameter * 1.25f; }

public:
	float timeStep;
	float particleDiameter;
	Geom::Box boundaryBox;
	Geom::Vector3d externalForce;
};

	}
}

#endif