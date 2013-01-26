#ifndef __SIMULATION_SETTING_H__
#define __SIMULATION_SETTING_H__

#include "../CryphousGeometry/Vector3d.h"
#include "../CryphousGeometry/Box.h"

#include "Uncopyable.h"

namespace Cryphous{
	namespace Physics{

class SimulationSetting : private Uncopyable
{
public:
	SimulationSetting(void) :
	  timeStep( 0.02f ),
	  particleDiameter(0.5f),
	  boundaryBox( Geometry::Vector3d(-20.0f, 0.0f, -20.0f), Geometry::Vector3d(20.0f, 100.0f, 20.0f) ),
	  externalForce( Geometry::Vector3d( 0.0f, -9.8f, 0.0f ) )
	  {};

	~SimulationSetting(){};

	float getEffectLength() const { return particleDiameter * 1.25f; }

public:
	float timeStep;
	float particleDiameter;
	Geometry::Box boundaryBox;
	Geometry::Vector3d externalForce;
};

	}
}

#endif