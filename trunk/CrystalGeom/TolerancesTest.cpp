#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>

#include "../CrystalGeom/Tolerances.h"

using namespace Crystal::Geom;

BOOST_AUTO_TEST_CASE(TOLERANCES_TEST)
{
	BOOST_CHECK( Tolerances::isEqualAsDistance( 1.0, 1.0 ) );
	BOOST_CHECK( !Tolerances::isEqualAsDistance( 1.0, 5.0 ) );

	BOOST_CHECK( Tolerances::isEqualAsDenominator( 1.0, 1.0 ) );
	BOOST_CHECK( !Tolerances::isEqualAsDenominator( 1.0, 5.0 ) );
}