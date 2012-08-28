#ifndef __SIMULATION_SETTING_H__
#define __SIMULATION_SETTING_H__

#include "../CrystalGeom/Vector3d.h"
#include "../CrystalGeom/Box.h"

#include <boost/noncopyable.hpp>

namespace Crystal{
	namespace Physics{

class SimulationSetting //: private boost::noncopyable
{
public:
	SimulationSetting(void) :
	  timeStep( 0.0075f ),
	  particleDiameter(0.1f),
	  boundaryBox( Geom::Vector3d(-10.0f, 0.0f, -10.0f), Geom::Vector3d(10.0f, 100.0f, 10.0f) )
	  {};

	~SimulationSetting(){};

	float getEffectLength() const { return particleDiameter * 1.25f; }

public:
	float timeStep;
	float particleDiameter;
	Geom::Box boundaryBox;
};

	}
}

#endif