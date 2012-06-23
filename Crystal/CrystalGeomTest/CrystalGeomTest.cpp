#define BOOST_TEST_MODULE CRYSTAL_GEOM_TEST
#include <boost/test/unit_test.hpp>

#include "TolerancesTest.h"
#include "Vector3dTest.h"
#include "BoxTest.h"
#include "Matrix3dTest.h"
#include "QuaternionTest.h"


BOOST_AUTO_TEST_CASE( CrystalGeomTest )
{
	TolerancesTest tolerancesTest;
	Vector3dTest vector3dTest;
	BoxTest boxTest;
	Matrix3dTest matrix3dTest;
	QuaternionTest quaternionTest;
}