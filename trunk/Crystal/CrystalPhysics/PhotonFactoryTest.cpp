#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>

#include "../CrystalPhysics/PhotonFactory.h"

#include "../CrystalGeom/Vector3d.h"

using namespace Crystal::Geom;
using namespace Crystal::Physics;

BOOST_AUTO_TEST_CASE(PHOTON_FACTORY_TEST)
{
	std::vector<Vector3d> points;
	points.push_back( Vector3d(0.0, 0.0, 0.0 ) );
	points.push_back( Vector3d(1.0, 0.0, 0.0 ) );
	std::vector<Vector3d> velocities;
	velocities.push_back( Vector3d( 1.0, 0.0, 0.0 ) );
	velocities.push_back( Vector3d( 0.0, 1.0, 0.0 ) );
	PhotonFactory factory;
	factory.addPhotons( points, velocities );

	const PhotonVector& photons = factory.getPhotons();

	BOOST_CHECK_EQUAL( photons.size(), 2);

	BOOST_CHECK_EQUAL( photons[0]->id, 0 );
	BOOST_CHECK_EQUAL( photons[1]->id, 1 );

	BOOST_CHECK( photons[0]->center == points[0] );
	BOOST_CHECK( photons[1]->center == points[1] );

	BOOST_CHECK( photons[0]->velocity == velocities[0] );
	BOOST_CHECK( photons[1]->velocity == velocities[1] );
}
