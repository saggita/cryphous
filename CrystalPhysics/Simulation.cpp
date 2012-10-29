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

#include "PhotonSolver.h"
#include "SearchPhotonFactory.h"

#include <omp.h>

#include <cassert>
#include <cmath>

using namespace Crystal::Geom;
using namespace Crystal::Physics;

void Simulation::simulate(PhysicsObjectFactory* factory, LightSourceFactory* lightSourceFactory, const SimulationSetting& setting)
{
	Profiler::get()->start("Simulation->");

	PhysicsObjectVector& physicsObjects = factory->getPhysicsObjects();

	Profiler::get()->start(" Sim->sorting");	
	SearchParticleFactory spFactory( factory->getParticles(), setting.getEffectLength() );
	const SearchParticleVector& sortedParticles = spFactory.getSearchParticles();
	Profiler::get()->end(" Sim->sorting");

	Profiler::get()->start(" Sim->sortingP");
	SearchPhotonFactory photonFactory( lightSourceFactory->getPhotons(), setting.getEffectLength() );
	const SearchPhotonVector& sortedPhotons = photonFactory.getSearchPhotons();
	Profiler::get()->end(" Sim->sortingP");

	SPHSolver solver( factory, setting, sortedParticles);
	solver.calculateInteraction();

	const ParticleVector& particles = factory->getParticles();

	for(Particle* particle: particles ) { particle->force += setting.externalForce * particle->density; }

	for(PhysicsObject* object: physicsObjects ) { object->enforce( setting.timeStep ); }
	
	for(PhysicsObject* object: physicsObjects ) { object->integrateTime( setting.timeStep ); }

	PhotonSolver photonSolver( lightSourceFactory, setting );
	photonSolver.calculateInteraction( sortedParticles, sortedPhotons);
	
	const LightSourceVector& lightSources = lightSourceFactory->getLightSources();
	for( LightSource* lightSource : lightSources ) { lightSource->integrateTime( setting.timeStep ); }

	++step;
	simulationTime += setting.timeStep;

	Profiler::get()->end("Simulation->");
}