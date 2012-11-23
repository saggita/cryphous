#include "StdAfx.h"
#include "ColorXYZ.h"

#include "ColorRGBA.h"

using namespace Amorphous::Geom;
using namespace Amorphous::Color;

ColorXYZ::ColorXYZ(const ColorRGBA<> &color4d)
{
	const Matrix3d<>& matrix = getToXYZMatrix();
	const Vector3d<> vector( color4d.getRed(), color4d.getGreen(), color4d.getBlue() );
	const Vector3d<>& result = matrix * vector;
	x = result.getX();
	y = result.getY();
	z = result.getZ();
}

ColorRGBA<> ColorXYZ::convertToRGB() const
{
	const Matrix3d<>& matrix = getToRGBMatrix();
	const Vector3d<> vector( x, y, z );
	const Vector3d<>& result = matrix * vector;
	return ColorRGBA<>( result.getX(), result.getY(), result.getZ());
}

Matrix3d<> ColorXYZ::getToRGBMatrix() const
{
	return Matrix3d<>( 3.240479, -1.53715, - 0.498535,
		-0.969256, 1.875991, 0.041556,
		0.055648, - 0.204043, 1.057311);
}

Matrix3d<> ColorXYZ::getToXYZMatrix() const
{
	return getToRGBMatrix().getInverse();
}