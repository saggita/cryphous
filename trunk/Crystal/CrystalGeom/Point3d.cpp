#include "Point3d.h"
#include "Tolerances.h"
#include "Vector3d.h"
#include "Matrix3d.h"

#include <cmath>
#include <cassert>
#include <cstdlib>

using namespace Crystal::Geom;


/// コンストラクタ.
Point3d::Point3d(const Vector3d& vector) :
x( vector.getX() ),
y( vector.getY() ),
z( vector.getZ() )
{
}

bool Point3d::equals(const Point3d& rhs) const
{
	return Tolerances::isEqualAsDistance( getDistance( rhs ) );
}

/// 回転する.
void Point3d::rotate( const Matrix3d& matrix )
{
	*(this) = getRotated( matrix );
}

/// 回転後の点を取得する.
Point3d Point3d::getRotated( const Matrix3d& matrix ) const
{
	return Point3d( 
		matrix.x00 * x + matrix.x01 * y + matrix.x02 * z,
		matrix.x10 * x + matrix.x11 * y + matrix.x12 * z,
		matrix.x20 * x + matrix.x21 * y + matrix.x22 * z
		);
}

void Point3d::addPertubation(const double xRange, const double yRange, const double zRange)
{
	const Geom::Vector3d pertubation( (rand() % 10 ) / 10.0 * xRange,
				(rand() % 10 ) / 10.0 * yRange,
				(rand() % 10 ) / 10.0 * zRange );
	(*this) += pertubation;
}

Point3d Point3d::getPertubated(const double xRange, const double yRange, const double zRange) const
{
	Point3d pertubated = *(this);
	pertubated.addPertubation( xRange, yRange, zRange );
	return pertubated;
}