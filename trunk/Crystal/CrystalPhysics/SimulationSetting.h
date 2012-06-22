#ifndef __SIMULATION_SETTING_H__
#define __SIMULATION_SETTING_H__

#include "../CrystalGeom/Box.h"

#include <boost/noncopyable.hpp>

namespace Crystal{
	namespace Physics{

class SimulationSetting : private boost::noncopyable
{
public:
	SimulationSetting(void) :
	  timeStep( 0.0025 ),
	  particleDiameter(1.0)
	  {};

	~SimulationSetting(){};

	double getEffectLength() const { return particleDiameter * 1.25; }

public:
	double timeStep;
	double particleDiameter;
	Geom::Box boundaryBox;
};

	}
}

#endif