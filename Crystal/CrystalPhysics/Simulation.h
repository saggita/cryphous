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

#include <boost/foreach.hpp>

#include <cassert>
#include <cmath>

#include "../CrystalUtility/Uncopyable.h"

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

		PhysicsObjectList& physicsObjects = factory->getPhysicsObjects();

		SPHSolver solver( factory, setting);
		solver.calculateInteraction();

		const ParticleVector& particles = factory->getSortedParticles();

		BOOST_FOREACH( Particle* particle, particles ) {
			particle->force += Geom::Vector3d( 0.0f, -9.8f * particle->density, 0.0f );
		}

		Profiler::get()->start(" Sim->enforce");
		BOOST_FOREACH( PhysicsObject* object, physicsObjects ) {
			object->enforce( setting.timeStep );
		}
		Profiler::get()->end(" Sim->enforce");

		Profiler::get()->start(" Sim->integrate");
		BOOST_FOREACH( PhysicsObject* object, physicsObjects ) {
			object->integrateTime( setting.timeStep );
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