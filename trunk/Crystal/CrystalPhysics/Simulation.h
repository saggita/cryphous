#ifndef __SIMULATION_H__
#define __SIMULATION_H__

#include "SPHSolver.h"
#include "PhysicsObject.h"

#include "PhysicsObjectFactory.h"
#include "../CrystalGeom/Box.h"
#include "../CrystalGeom/Vector3d.h"
#include "../CrystalGeom/Vector3d.h"

#include "Particle.h"
#include "SimulationSetting.h"
#include "Profiler.h"

#include <cassert>
#include <cmath>

#include "Uncopyable.h"

namespace Crystal{
	namespace Physics {
		
class Simulation : private Uncopyable
{
public:
	Simulation() :step(0), simulationTime(0.0){};

	~Simulation() {};

	void init() { 
		step = 0;
		simulationTime = 0.0;
	};

	void simulate(PhysicsObjectFactory* factory, const SimulationSetting& setting)
	{
		Profiler::get()->start("Simulation->");

		PhysicsObjectVector& physicsObjects = factory->getPhysicsObjects();

		SPHSolver solver( factory, setting);
		solver.calculateInteraction();

		const ParticleVector& particles = factory->getParticles();
		for( ParticleVector::const_iterator iter = particles.begin(); iter != particles.end(); ++iter ) {
			(*iter)->force += Geom::Vector3d( 0.0f, -9.8f * (*iter)->density, 0.0f );
		}

		Profiler::get()->start(" Sim->enforce");
		for( PhysicsObjectVector::const_iterator iter = physicsObjects.begin(); iter != physicsObjects.end(); ++iter ) {
			(*iter)->enforce( setting.timeStep );
		}
		Profiler::get()->end(" Sim->enforce");

		Profiler::get()->start(" Sim->integrate");
		for( PhysicsObjectVector::const_iterator iter = physicsObjects.begin(); iter != physicsObjects.end(); ++iter ) {
			(*iter)->integrateTime( setting.timeStep );
		}
		Profiler::get()->end(" Sim->integrate");

		++step;
		simulationTime += setting.timeStep;

		Profiler::get()->end("Simulation->");
	}

	int getStep() const { return step; }

	float getSimulationTime() const { return simulationTime; }

private:
	int step;
	float simulationTime;
};

	}
}

#endif