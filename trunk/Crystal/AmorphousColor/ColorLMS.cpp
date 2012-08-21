#include "StdAfx.h"
#include "ColorLMS.h"

#include "ColorXYZ.h"

#include <cassert>

using namespace Crystal::Geom;
using namespace Crystal::Color;

ColorLMS::ColorLMS(const double l, const double m, const double s) :
l(l),
m(m),
s(s)
{
}

ColorLMS::ColorLMS(const ColorXYZ& colorXYZ)
{
	const Matrix3d& matrix = getToLMSMatrix();
	const Vector3d vector( colorXYZ.getX(), colorXYZ.getY(), colorXYZ.getZ() );
	const Vector3d& converted = matrix * vector;
	l = converted.getX();
	m = converted.getY();
	s = converted.getZ();
}

ColorLMS::~ColorLMS(void)
{
}

ColorXYZ ColorLMS::getColorXYZ() const
{
	const Matrix3d& matrix = getToXYZMatrix();
	const Vector3d vector( l, m, s);
	const Vector3d& converted = matrix * vector;
	return ColorXYZ( converted.getX(), converted.getY(), converted.getZ() );
}

Matrix3d ColorLMS::getToLMSMatrix()
{
	return Matrix3d( 0.8951, 0.2664, -0.1614,
		-0.7502, 1.7135, 0.0367,
		0.0389, -0.0685, 1.0296);
}

Matrix3d ColorLMS::getToXYZMatrix()
{
	return getToLMSMatrix().getInverse();
}