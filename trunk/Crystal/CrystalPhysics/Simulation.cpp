#include "Simulation.h"

#include "SPHSolver.h"
#include "PhysicsObject.h"

#include "PhysicsObjectFactory.h"
#include "PhysicsObjectCondition.h"
#include "../CrystalGeom/Box.h"
#include "../CrystalGeom/Point3d.h"
#include "../CrystalGeom/Vector3d.h"

#include "Particle.h"
#include "ParticleDerive.h"

#include "SimulationSetting.h"

#include "Profiler.h"

#include <boost/foreach.hpp>

#include <cassert>
#include <cmath>

using namespace Crystal::Geom;
using namespace Crystal::Physics;

void Simulation::simulate(PhysicsObjectFactory* factory)
{
	Profiler::get()->start("SimulationTotal");

	PhysicsObjectList& physicsObjects = factory->getPhysicsObjects();

	SPHSolver solver( factory, SimulationSetting::get()->effectLength);
	solver.calculateInteraction();

	const ParticleVector& particles = factory->getSortedParticles();

	BOOST_FOREACH( Particle* particle, particles ) {
		particle->getDerive()->force += Vector3d( 0.0, -9.8 * particle->getDensity(), 0.0 );
	}

	Profiler::get()->start(" Sim->enforce");
	BOOST_FOREACH( PhysicsObject* object, physicsObjects ) {
		object->enforce( SimulationSetting::get()->timeStep );
	}
	Profiler::get()->end(" Sim->enforce");

	Profiler::get()->start(" Sim->timeIntegrate");
	BOOST_FOREACH( PhysicsObject* object, physicsObjects ) {
		object->integrateTime( SimulationSetting::get()->timeStep );
	}
	Profiler::get()->end(" Sim->timeIntegrate");

	++step;
	simulationTime += SimulationSetting::get()->timeStep;

	Profiler::get()->end("SimulationTotal");
}
