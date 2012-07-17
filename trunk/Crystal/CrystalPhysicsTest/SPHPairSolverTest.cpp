#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>

#include "../CrystalPhysics/SPHPairSolver.h"
#include "../CrystalPhysics/ParticleFactory.h"
#include "../CrystalPhysics/Particle.h"
#include "../CrystalPhysics/ParticlePair.h"
#include "../CrystalPhysics/PhysicsObjectFactory.h"
#include "../CrystalPhysics/PhysicsObject.h"

#include "../CrystalGeom/Box.h"
#include "../CrystalGeom/Vector3d.h"

using namespace Crystal::Geom;
using namespace Crystal::Physics;

BOOST_AUTO_TEST_CASE(SPH_PAIR_SOLVER_TEST)
{
	{
		PhysicsObjectFactory factory;
		SimulationSetting setting;
		setting.particleDiameter = 1.0;
		std::vector<Vector3d> points;
		points.push_back( Vector3d(0.0f, 0.0f, 0.0f ) );
		points.push_back( Vector3d(1.0f, 0.0f, 0.0f ) );
		PhysicsObjectCondition conditionFluid( points, 1000.0f, 1.0f, 0.4f, PhysicsObjectCondition::Fluid ); 
		PhysicsObject* fluid = factory.createPhysicsObject( conditionFluid, setting);

		const ParticleVector& particles = factory.getPhysicsObjects().front()->getParticles();
		ParticlePair pair( particles.front(), particles.back() );

		SPHPairSolver solver( 1.3f );
		solver.calculateDensity( pair);
		const float densityX = particles.front()->density;
		const float densityY = particles.back()->density;
		BOOST_CHECK( densityX != 0.0f );
		BOOST_CHECK( densityY != 0.0f );
		BOOST_CHECK_EQUAL( densityX, densityY );
	}

	{
		PhysicsObjectFactory factory;
		std::vector<Vector3d> points;
		points.push_back( Vector3d(0.0f, 0.0f, 0.0f ) );
		points.push_back( Vector3d(1.0f, 0.0f, 0.0f ) );SimulationSetting setting;
		setting.particleDiameter = 1.0f;
		PhysicsObjectCondition conditionFluid( points, 1000.0f, 1.0f, 0.4f, PhysicsObjectCondition::Fluid ); 
		PhysicsObject* fluid = factory.createPhysicsObject( conditionFluid, setting);
		const ParticleVector&	particles = factory.getPhysicsObjects().front()->getParticles();
		ParticlePair pair( particles.front(), particles.back() );

		SPHPairSolver solver( 1.3f );
		solver.calculateBoundaryDensity( pair);
		const float densityX = particles.front()->density;
		const float densityY = particles.back()->density;
		BOOST_CHECK( densityX != 0.0f );
		BOOST_CHECK( densityY != 0.0f );
		BOOST_CHECK_EQUAL( densityX, densityY );
	}

	{
		PhysicsObjectFactory factory;
		std::vector<Vector3d> points;
		points.push_back( Vector3d(0.0f, 0.0f, 0.0f ) );
		points.push_back( Vector3d(1.0f, 0.0f, 0.0f ) );
		SimulationSetting setting;
		setting.particleDiameter = 1.0f;
		PhysicsObjectCondition conditionFluid( points, 1000.0f, 1.0f, 0.4f, PhysicsObjectCondition::Fluid ); 
		PhysicsObject* fluid = factory.createPhysicsObject( conditionFluid, setting);
		const ParticleVector& particles = factory.getPhysicsObjects().front()->getParticles();
		ParticlePair pair( particles.front(), particles.back() );

		SPHPairSolver solver( 1.3f );
		solver.calculateDensity( pair );
		solver.calculatePressureForce( pair);
		const Vector3d& forceX = particles.front()->force;
		const Vector3d& forceY = particles.back()->force;
		BOOST_CHECK( !forceX.isZero() );
		BOOST_CHECK( !forceY.isZero() );
		BOOST_CHECK( forceX == forceY * -1.0f );
	}
}
