#pragma once

#include "Point3d.h"
#include "Vector3d.h"
#include "Quaternion.h"

namespace Crystal{
	namespace Geom{

/// 幾何プリミティブ.
class Primitive
{
public:

	enum Type{
		Box,
		Sphere,
		Cylinder
	};

	/// デストラクタ.
	virtual ~Primitive() {};

	/// コンストラクタ.
	Primitive(const Point3d& pointX, const Point3d& pointY, const Type type);

	/// コンストラクタ.
	//Primitive(const Point3d& center, const double radius);

	/// 体積を取得する.
	//virtual double getVolume() const;

	Primitive* createClone() const { return new Primitive(*this);  }

	/// 最大頂点を取得する.
	Point3d getMax() const { return Point3d( getMaxX(), getMaxY(), getMaxZ() ); }

	/// 最小頂点を取得する.
	Point3d getMin() const { return Point3d( getMinX(), getMinY(), getMinZ() ); }

	/// 最大Xを取得する.
	double getMaxX() const { return maxX + center.getX(); }

	/// 最小Xを取得する.
	double getMinX() const { return minX + center.getX(); }

	/// 最大Yを取得する.
	double getMaxY() const { return maxY + center.getY(); }

	/// 最小Yを取得する.
	double getMinY() const { return minY + center.getY(); }

	/// 最大Zを取得する.
	double getMaxZ() const { return maxZ + center.getZ(); }

	/// 最小Zを取得する.
	double getMinZ() const { return minZ + center.getZ(); }

	/// 点がプリミティブ内部か.
	bool isInterior(const Point3d& point) const;

	/// 点がプリミティブ外部か.
	bool isExterior(const Point3d& point) const;

	Point3d getCenter() const { return center; }

	Type getType() const { return type; }

	void move( const Vector3d& moveVector ) { center += moveVector; }

private:
	double maxX;	///< 最大X.
	double minX;	///< 最小X.
	double maxY;	///< 最大Y.
	double minY;	///< 最小Y.
	double maxZ;	///< 最大Z.
	double minZ;	///< 最大Z.

	Point3d center;
	Type type;
	//Quaternion quaternion;
};

	}	// namespace Geom
}	// namespace Crystal