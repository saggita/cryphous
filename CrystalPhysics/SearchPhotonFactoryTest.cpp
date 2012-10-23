#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>

#include "../CrystalPhysics/SearchPhotonFactory.h"
#include "../CrystalPhysics/SearchPhoton.h"

#include "../CrystalPhysics/Photon.h"
#include "../CrystalPhysics/PhotonFactory.h"

using namespace Crystal::Geom;
using namespace Crystal::Physics;

BOOST_AUTO_TEST_CASE( SEARCH_PHOTON_FACTORY_TEST )
{
	std::vector<Vector3d> points;
	std::vector<Vector3d> velocities;
	points.push_back( Vector3d( 0.0f, 0.0f, 0.0f ) );
	velocities.push_back( Vector3d( 1.0f, 0.0f, 0.0f ) );
	PhotonFactory factory;
	const PhotonVector& photons = factory.addPhotons( points, velocities );
	BOOST_CHECK_EQUAL( photons.size(), 1 );
	SearchPhotonFactory spFactory( photons, 1.0f );
	const SearchPhotonVector& sorted = spFactory.getSearchPhotons();
	BOOST_CHECK_EQUAL( sorted.size(), 1 );
}