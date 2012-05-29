#ifndef __QUATERNION_H__
#define __QUATERNION_H__

namespace Crystal{
	namespace Geom{

class Vector3d;
class Matrix3d;

class Quaternion
{
public:

	Quaternion(void);

	Quaternion(const double x, const double y, const double z, const double w);

	Quaternion(const Vector3d& axis, const double angle);

	Matrix3d getMatrix() const;

	Quaternion& operator+=( const Quaternion& rhs );

	//Quaternion& operator*=( const Quaternion& rhs );

	double getX() const { return x; }

	double getY() const { return y; }

	double getZ() const { return z; }

	double getW() const { return w; }

	double getNorm() const;

	Quaternion& normalize();

	bool isNormalized() const;

private:
	double x;
	double y;
	double z;
	double w;
};

	}
}

#endif