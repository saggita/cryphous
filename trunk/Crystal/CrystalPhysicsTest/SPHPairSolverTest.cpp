#include "SPHPairSolverTest.h"

#include "../CrystalPhysics/SPHPairSolver.h"
#include "../CrystalPhysics/ParticleFactory.h"
#include "../CrystalPhysics/Particle.h"
#include "../CrystalPhysics/ParticlePair.h"
#include "../CrystalPhysics/ParticleDerive.h"
#include "../CrystalPhysics/PhysicsObjectFactory.h"
#include "../CrystalPhysics/PhysicsObject.h"
#include "../CrystalPhysics/PhysicsObjectCondition.h"

#include "../CrystalGeom/Box.h"
#include "../CrystalGeom/Point3d.h"

#include <boost/test/unit_test.hpp>

using namespace Crystal::Geom;
using namespace Crystal::Physics;

SPHPairSolverTest::SPHPairSolverTest()
{
	createFactory();
	calculateDensityTest();
	calculatePressureForceTest();
	calculateBoundaryDensityTest();
}

SPHPairSolverTest::~SPHPairSolverTest()
{
	PhysicsObjectFactory::get()->init();
}

void SPHPairSolverTest::calculateDensityTest()
{
	const ParticleVector&	particles = PhysicsObjectFactory::get()->getPhysicsObjects().front()->getParticles();
	ParticlePair pair( particles.front(), particles.back() );

	SPHPairSolver solver( 1.3 );
	solver.calculateDensity( &pair);
	const double densityX = particles.front()->getDensity();
	const double densityY = particles.back()->getDensity();
	BOOST_CHECK( densityX != 0.0 );
	BOOST_CHECK( densityY != 0.0 );
	BOOST_CHECK_EQUAL( densityX, densityY );
}

void SPHPairSolverTest::calculateBoundaryDensityTest()
{
	const ParticleVector&	particles = PhysicsObjectFactory::get()->getPhysicsObjects().front()->getParticles();
	ParticlePair pair( particles.front(), particles.back() );

	SPHPairSolver solver( 1.3 );
	solver.calculateBoundaryDensity( &pair);
	const double densityX = particles.front()->getDensity();
	const double densityY = particles.back()->getDensity();
	BOOST_CHECK( densityX != 0.0 );
	BOOST_CHECK( densityY != 0.0 );
	BOOST_CHECK_EQUAL( densityX, densityY );
}

void SPHPairSolverTest::calculatePressureForceTest()
{
	const ParticleVector& particles = PhysicsObjectFactory::get()->getPhysicsObjects().front()->getParticles();
	ParticlePair pair( particles.front(), particles.back() );

	SPHPairSolver solver( 1.3 );
	solver.calculatePressureForce( &pair);
	const Vector3d& forceX = particles.front()->getDerive()->force;
	const Vector3d& forceY = particles.back()->getDerive()->force;
	BOOST_CHECK( !forceX.isZero() );
	BOOST_CHECK( !forceY.isZero() );
	BOOST_CHECK( forceX == forceY * -1.0 );
}

void SPHPairSolverTest::createFactory()
{
	Box box( Point3d( 0.0, 0.0, 0.0), Point3d( 1.0, 2.0, 1.0 ) );
	PhysicsObjectCondition conditionFluid( box, 1000.0, 1.0, 5.0, 0.4, PhysicsObjectCondition::Fluid ); 
	PhysicsObject* fluid = PhysicsObjectFactory::get()->createPhysicsObject( conditionFluid, 1.0);
}