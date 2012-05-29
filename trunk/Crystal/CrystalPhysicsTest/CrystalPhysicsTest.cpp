#define BOOST_TEST_MODULE CRYSTAL_PHYSICS_TEST
#include <boost/test/unit_test.hpp>

#include "ParticleConditionsTest.h"
#include "SPHPairSolverTest.h"
#include "ParticleFactoryTest.h"
#include "PhysicsObjectFactoryTest.h"
#include "BoundarySolverTest.h"
#include "SPHSolverTest.h"
#include "SimulationTest.h"
#include "SpringTest.h"
#include "SpringParticleFactoryTest.h"
#include "SearchParticleFactoryTest.h"
#include "NeighborSearcherTest.h"

BOOST_AUTO_TEST_CASE( CrystalPhysicsTest )
{
	ParticleConditionsTest particleConditionsTest;
	SPHPairSolverTest sphPairSolverTest;
	ParticleFactoryTest particleFactoryTest;
	PhysicsObjectFactoryTest physicsObjectFactoryTest;
	NeighborSearcherTest neighborSearcherTest;
	BoundarySolverTest boundarySolverTest;
	SPHSolverTest sphSolverTest;
	SimulationTest simulationTest;
	SpringTest springTest;
	SpringParticleFactoryTest springParticleFactoryTest;
	SearchParticleFactoryTest searchParticleFactoryTest;
}