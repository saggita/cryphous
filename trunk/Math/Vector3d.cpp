#include "Vector3d.h"

#include "Matrix3d.h"

using namespace Crystal::Math;

Vector3d::Vector3d(void) :
	x( 0.0 ), y( 0.0 ), z( 0.0 )
{
}

Vector3d::Vector3d( float x, float y, float z ) :
	x( x), y( y), z( z)
{
}

Vector3d::Vector3d( const Vector3d& start, const Vector3d& end ) :
	x( end.x - start.x ),
	y( end.y - start.y ),
	z( end.z - start.z )
{
}

Vector3d Vector3d::scale( const float factor )
{
	x *= factor;
	y *= factor;
	z *= factor;
	return *this;
}

Vector3d Vector3d::getScaled( const float factor ) const
{
	return Vector3d( x * factor, y * factor, z * factor );
}

bool Vector3d::isNormalized() const
{
	return Tolerances::isEqualLoosely( getLength(), 1.0 );
}

bool Vector3d::equals( const Vector3d &rhs ) const 
{
	return Tolerances::isEqualLoosely( getDistance( rhs ) );
}

bool Vector3d::isZero() const
{
	return Tolerances::isEqualLoosely( getLength() );
}

bool Vector3d::operator==( const Vector3d& rhs ) const
{
	return equals( rhs );
}

bool Vector3d::operator!=( const Vector3d& rhs ) const
{
	return !equals( rhs );
}

Vector3d Vector3d::normalize()
{
	const float length = getLength();
	x /= length;
	y /= length;
	z /= length;
	return *this;
}

Vector3d Vector3d::getNormalized() const
{
	Vector3d vector = *(this);
	return vector.normalize();
}

void Vector3d::setZero()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

float Vector3d::getLengthSquared() const
{
	return x * x + y * y + z * z;
}

float Vector3d::getLength() const {
	return ::sqrt( getLengthSquared() );
}

float Vector3d::getDistance( const Vector3d& rhs ) const
{
	return ::sqrt( getDistanceSquared( rhs ) );
}

float Vector3d::getDistanceSquared( const Vector3d& rhs ) const
{
	return pow( x - rhs.x, 2 ) + pow( y - rhs.y, 2 ) + pow( z - rhs.z, 2 );
}

void Vector3d::rotate(const Matrix3d& matrix)
{
	*(this) = getRotated( matrix );
}

Vector3d Vector3d::getRotated( const Matrix3d& matrix ) const
{
	const float x = matrix.getX00() * this->x + matrix.getX01() * this->y + matrix.getX02() * this->z;
	const float y = matrix.getX10() * this->x + matrix.getX11() * this->y + matrix.getX12() * this->z;
	const float z = matrix.x20 * this->x + matrix.x21 * this->y + matrix.x22 * this->z;
		
	return Vector3d( x, y, z );
}

Vector3d Vector3d::getMult( const Matrix3d& matrix ) const
{
	return Vector3d ( 
		x * matrix.getX00() + y * matrix.getX10() + z * matrix.x20,
		x * matrix.getX01() + y * matrix.getX11() + z * matrix.x21,
		x * matrix.getX02() + y * matrix.getX12() + z * matrix.x22
		);
}
	
const Vector3d Vector3d::operator*( const Matrix3d& rhs ) const 
{
	return getMult( rhs );
}

Vector3d Vector3d::operator+=( const Vector3d& rhs )
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}

Vector3d Vector3d::operator-=( const Vector3d& rhs )
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	return *this;
}

Vector3d Vector3d::operator*( const float factor ) const
{
	Vector3d vector( *this );
	return vector.scale( factor );
}

Vector3d Vector3d::operator/( const float factor ) const
{
	Vector3d vector( *this );
	return vector.scale( 1.0f / factor );
}

Vector3d Vector3d::operator+( const Vector3d& rhs ) const
{
	return Vector3d( x + rhs.x, y + rhs.y, z + rhs.z );
}

Vector3d Vector3d::operator-( const Vector3d& rhs ) const
{
	return Vector3d( x - rhs.x, y - rhs.y, z - rhs.z );
}