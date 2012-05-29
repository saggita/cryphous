#include "Point4d.h"
#include "Tolerances.h"
#include "Vector4d.h"
#include "Matrix4d.h"
#include "Point3d.h"

#include <cmath>
#include <cassert>
#include <cstdlib>

using namespace Crystal::Geom;

Point4d::Point4d(const Vector4d& vector) :
x( vector.getX() ),
y( vector.getY() ),
z( vector.getZ() ),
w( vector.getW() )
{
}

bool Point4d::equals(const Point4d& rhs) const
{
	return Tolerances::isEqualAsDistance( getDistance( rhs ) );
}

void Point4d::rotate( const Matrix4d& matrix )
{
	*(this) = getRotated( matrix );
}

Point4d Point4d::getRotated( const Matrix4d& matrix ) const
{
	return Point4d( 
		matrix.x00 * x + matrix.x01 * y + matrix.x02 * z + matrix.x03 * w,
		matrix.x10 * x + matrix.x11 * y + matrix.x12 * z + matrix.x13 * w,
		matrix.x20 * x + matrix.x21 * y + matrix.x22 * z + matrix.x23 * w,
		matrix.x30 * x + matrix.x31 * y + matrix.x32 * z + matrix.x33 * w
		);
}

Point3d Point4d::getPoint3d() const
{
	assert( !Tolerances::isEqualAsDenominator( w ) );
	return Point3d( x / w, y / w, z / w );
}