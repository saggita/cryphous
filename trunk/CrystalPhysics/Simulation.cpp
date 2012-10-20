#include "Simulation.h"

#include "../CrystalGeom/Box.h"
#include "../CrystalGeom/Vector3d.h"
#include "../CrystalGeom/Vector3d.h"

#include "SPHSolver.h"
#include "PhysicsObject.h"

#include "PhysicsObjectFactory.h"
#include "Particle.h"
#include "SimulationSetting.h"
#include "Profiler.h"

#include "LightSourceFactory.h"
#include "BoundaryPhotonSolver.h"

#include <omp.h>

#include <cassert>
#include <cmath>

using namespace Crystal::Geom;
using namespace Crystal::Physics;

void Simulation::simulate(PhysicsObjectFactory* factory, LightSourceFactory* lightSourceFactory, const SimulationSetting& setting)
{
	Profiler::get()->start("Simulation->");

	PhysicsObjectVector& physicsObjects = factory->getPhysicsObjects();

	SPHSolver solver( factory, setting);
	solver.calculateInteraction();

	const ParticleVector& particles = factory->getParticles();

	for(Particle* particle: particles ) { particle->force += setting.externalForce * particle->density; }

	for(PhysicsObject* object: physicsObjects ) { object->enforce( setting.timeStep ); }
	
	for(PhysicsObject* object: physicsObjects ) { object->integrateTime( setting.timeStep ); }
	
	const LightSourceVector& lightSources = lightSourceFactory->getLightSources();

	for( LightSource* lightSource : lightSources ) {
		BoundaryPhotonSolver solver( lightSource );
		solver.reflectPhoton( setting.boundaryBox );
	}

	for( LightSource* lightSource : lightSources ) { lightSource->integrateTime( setting.timeStep ); }

	++step;
	simulationTime += setting.timeStep;

	Profiler::get()->end("Simulation->");
}