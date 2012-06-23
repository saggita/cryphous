#include "SPHPairSolverTest.h"

#include "../CrystalPhysics/SPHPairSolver.h"
#include "../CrystalPhysics/ParticleFactory.h"
#include "../CrystalPhysics/Particle.h"
#include "../CrystalPhysics/ParticlePair.h"
#include "../CrystalPhysics/PhysicsObjectFactory.h"
#include "../CrystalPhysics/PhysicsObject.h"
#include "../CrystalPhysics/PhysicsObjectCondition.h"

#include "../CrystalGeom/Box.h"
#include "../CrystalGeom/Vector3d.h"

#include <boost/test/unit_test.hpp>

using namespace Crystal::Geom;
using namespace Crystal::Physics;

SPHPairSolverTest::SPHPairSolverTest()
{
	calculateDensityTest();
	calculatePressureForceTest();
	calculateBoundaryDensityTest();
}

SPHPairSolverTest::~SPHPairSolverTest()
{
}

void SPHPairSolverTest::calculateDensityTest()
{
	PhysicsObjectFactory factory;
	Box box( Vector3d( 0.0, 0.0, 0.0), Vector3d( 1.0, 2.0, 1.0 ) );
	SimulationSetting setting;
	setting.particleDiameter = 1.0;
	PhysicsObjectCondition conditionFluid( box, 1000.0, 1.0, 0.4, PhysicsObjectCondition::Fluid ); 
	PhysicsObject* fluid = factory.createPhysicsObject( conditionFluid, setting);

	const ParticleVector& particles = factory.getPhysicsObjects().front()->getParticles();
	ParticlePair pair( particles.front(), particles.back() );

	SPHPairSolver solver( 1.3 );
	solver.calculateDensity( &pair);
	const double densityX = particles.front()->density;
	const double densityY = particles.back()->density;
	BOOST_CHECK( densityX != 0.0 );
	BOOST_CHECK( densityY != 0.0 );
	BOOST_CHECK_EQUAL( densityX, densityY );
}

void SPHPairSolverTest::calculateBoundaryDensityTest()
{
	PhysicsObjectFactory factory;
	Box box( Vector3d( 0.0, 0.0, 0.0), Vector3d( 1.0, 2.0, 1.0 ) );
	SimulationSetting setting;
	setting.particleDiameter = 1.0;
	PhysicsObjectCondition conditionFluid( box, 1000.0, 1.0, 0.4, PhysicsObjectCondition::Fluid ); 
	PhysicsObject* fluid = factory.createPhysicsObject( conditionFluid, setting);
	const ParticleVector&	particles = factory.getPhysicsObjects().front()->getParticles();
	ParticlePair pair( particles.front(), particles.back() );

	SPHPairSolver solver( 1.3 );
	solver.calculateBoundaryDensity( &pair);
	const double densityX = particles.front()->density;
	const double densityY = particles.back()->density;
	BOOST_CHECK( densityX != 0.0 );
	BOOST_CHECK( densityY != 0.0 );
	BOOST_CHECK_EQUAL( densityX, densityY );
}

void SPHPairSolverTest::calculatePressureForceTest()
{
	PhysicsObjectFactory factory;
	Box box( Vector3d( 0.0, 0.0, 0.0), Vector3d( 1.0, 2.0, 1.0 ) );
	SimulationSetting setting;
	setting.particleDiameter = 1.0;
	PhysicsObjectCondition conditionFluid( box, 1000.0, 1.0, 0.4, PhysicsObjectCondition::Fluid ); 
	PhysicsObject* fluid = factory.createPhysicsObject( conditionFluid, setting);
	const ParticleVector& particles = factory.getPhysicsObjects().front()->getParticles();
	ParticlePair pair( particles.front(), particles.back() );

	SPHPairSolver solver( 1.3 );
	solver.calculateDensity( &pair );
	solver.calculatePressureForce( &pair);
	const Vector3d& forceX = particles.front()->force;
	const Vector3d& forceY = particles.back()->force;
	BOOST_CHECK( !forceX.isZero() );
	BOOST_CHECK( !forceY.isZero() );
	BOOST_CHECK( forceX == forceY * -1.0 );
}