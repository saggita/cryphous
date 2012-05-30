#define BOOST_TEST_MODULE CRYSTAL_GEOM_TEST
#include <boost/test/unit_test.hpp>

#include "TolerancesTest.h"
#include "Point2dTest.h"
#include "Point3dTest.h"
#include "Point4dTest.h"
#include "Vector2dTest.h"
#include "Vector3dTest.h"
#include "Vector4dTest.h"
#include "BoxTest.h"
#include "Matrix2dTest.h"
#include "Matrix3dTest.h"
#include "Matrix4dTest.h"
#include "QuaternionTest.h"
#include "PrimitiveTest.h"
#include "LineTest.h"


BOOST_AUTO_TEST_CASE( CrystalGeomTest )
{
	TolerancesTest tolerancesTest;
	Point2dTest point2dTest;
	Point3dTest point3dTest;
	Point4dTest point4dTest;
	Vector2dTest vector2dTest;
	Vector3dTest vector3dTest;
	Vector4dTest vector4dTest;
	BoxTest boxTest;
	Matrix2dTest matrix2dTest;
	Matrix3dTest matrix3dTest;
	Matrix4dTest matrix4dTest;
	QuaternionTest quaternionTest;
	PrimitiveTest primitiveTest;
}