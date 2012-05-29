#include "UblasTest.h"

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <iostream>

#include "../CrystalGeom/Vector3d.h"
#include "../CrystalGeom/Matrix3d.h"

const int iteration = 1000000;

void testUblasVector()
{
	boost::numeric::ublas::vector<double> x(3);
	boost::numeric::ublas::vector<double> y(3);
	x[0] = 1.0; x[1] = 2.0; x[2] = 3.0;
	y[0] = 4.0; y[1] = 5.0; y[2] = 6.0;
	boost::numeric::ublas::outer_prod( x, y);
}

void testCrystalVector()
{
	Crystal::Geom::Vector3d x( 1.0, 2.0, 3.0 );
	Crystal::Geom::Vector3d y( 4.0, 5.0, 6.0 );
	x.getOuterProduct( y);
}

void testUblasMatrix()
{
	boost::numeric::ublas::matrix<double> matrixX(3,3);
	matrixX(0,0) = 0.0; matrixX(0,1) = 1.0; matrixX(0,2) = 2.0;
	matrixX(1,0) = 3.0; matrixX(1,1) = 4.0; matrixX(1,2) = 5.0;
	matrixX(2,0) = 6.0; matrixX(2,1) = 7.0; matrixX(2,2) = 8.0;
	boost::numeric::ublas::matrix<double> matrixY(3,3);
	matrixY.assign(matrixX);
	boost::numeric::ublas::prod( matrixX, matrixY);
}

void testCrystalMatrix()
{
	Crystal::Geom::Matrix3d matrixX( 0.0, 1.0, 2.0,
		3.0, 4.0, 5.0,
		6.0, 7.0, 8.0 );
	Crystal::Geom::Matrix3d matrixY = matrixX;
	matrixX.getProduct( matrixY);
}

UblasTest::UblasTest(void)
{
	testUblasVector();
	testCrystalVector();
	testUblasMatrix();
	testCrystalMatrix();
}

UblasTest::~UblasTest(void)
{
}
