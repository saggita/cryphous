#ifndef __SIMULATION_H__
#define __SIMULATION_H__

#include <boost/noncopyable.hpp>

namespace Crystal{
	namespace Physics {

class Simulation : private boost::noncopyable
{
private:
	Simulation() :step(0), simulationTime(0.0){};

	~Simulation() {};

public:

	static Simulation* get() { 
		static Simulation simulation;
		return &simulation;
	}

	void init() { 
		step = 0;
		simulationTime = 0.0;
	};

	void simulate();

	int getStep() const { return step; }

	double getSimulationTime() const { return simulationTime; }

private:
	int step;
	double simulationTime;
};

	}
}

#endif