
#include "BoundarySolverTest.h"

#include "../CrystalPhysics/BoundarySolver.h"

#include "../CrystalPhysics/ParticleFactory.h"
#include "../CrystalPhysics/Particle.h"
#include "../CrystalPhysics/ParticleConditions.h"
#include "../CrystalPhysics/PhysicsObject.h"
#include "../CrystalPhysics/PhysicsObjectFactory.h"
#include "../CrystalPhysics/PhysicsObjectCondition.h"

#include "../CrystalGeom/Box.h"
#include "../CrystalGeom/Point3d.h"

#include <boost/test/unit_test.hpp>

using namespace Crystal::Geom;
using namespace Crystal::Physics;

BoundarySolverTest::BoundarySolverTest(void)
{
	PhysicsObjectCondition condition( Box(), 1000.0, 1.0, 1.0, 0.0, PhysicsObjectCondition::Fluid );
	PhysicsObject* object = PhysicsObjectFactory::get()->createPhysicsObject( condition, 1.0 );
	Particle* virtualParticle = object->getParticleFactory()->getVirtualParticle();
	BoundarySolver solver( object, 1.3 );
	solver.calculateDensity( Box() );
}
