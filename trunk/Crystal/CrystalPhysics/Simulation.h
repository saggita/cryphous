#ifndef __SIMULATION_H__
#define __SIMULATION_H__

#include <boost/noncopyable.hpp>

namespace Crystal{
	namespace Physics {
		class PhysicsObjectFactory;
		class SimulationSetting;

class Simulation : private boost::noncopyable
{
public:
	Simulation() :step(0), simulationTime(0.0){};

	~Simulation() {};

	void init() { 
		step = 0;
		simulationTime = 0.0;
	};

	void simulate(PhysicsObjectFactory* factory, const SimulationSetting& setting);

	int getStep() const { return step; }

	float getSimulationTime() const { return simulationTime; }

private:
	int step;
	float simulationTime;
};

	}
}

#endif