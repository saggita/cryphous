#pragma once

#include "../CrystalGeom/Box.h"

#include <boost/noncopyable.hpp>

namespace Crystal{
	namespace Physics{

class SimulationSetting : private boost::noncopyable
{
public:
	SimulationSetting(void);

	~SimulationSetting(){};

public:
	double timeStep;
	double effectLength;
	Geom::Box boundaryBox;
};

	}
}