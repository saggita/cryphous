#include "TolerancesTest.h"

#include <boost/test/unit_test.hpp>

#include "../CrystalGeom/Tolerances.h"

using namespace Crystal::Geom;

TolerancesTest::TolerancesTest(void)
{
	BOOST_CHECK( Tolerances::isEqualAsDistance( 1.0, 1.0 ) );
	BOOST_CHECK( !Tolerances::isEqualAsDistance( 1.0, 5.0 ) );

	BOOST_CHECK( Tolerances::isEqualAsDenominator( 1.0, 1.0 ) );
	BOOST_CHECK( !Tolerances::isEqualAsDenominator( 1.0, 5.0 ) );
}