#include "Simulation.h"

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

using namespace Crystal::Geom;
using namespace Crystal::Physics;

void Simulation::simulate(PhysicsObjectFactory* factory, const SimulationSetting& setting)
{
	Profiler::get()->start("Simulation->");

	PhysicsObjectList& physicsObjects = factory->getPhysicsObjects();

	SPHSolver solver( factory, setting);
	solver.calculateInteraction();

	const ParticleVector& particles = factory->getSortedParticles();

	BOOST_FOREACH( Particle* particle, particles ) {
		particle->force += Vector3d( 0.0, -9.8 * particle->density, 0.0 );
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
