#pragma once

#include "../CrystalGeom/Box.h"

#include <boost/noncopyable.hpp>

namespace Crystal{
	namespace Physics{

class SimulationSetting : private boost::noncopyable
{
private:
	SimulationSetting(void);
	~SimulationSetting(){};

public:
	static SimulationSetting* get(){
		static SimulationSetting setting;
		return &setting;
	}

public:
	double timeStep;
	double effectLength;
	Geom::Box boundaryBox;
};

	}
}