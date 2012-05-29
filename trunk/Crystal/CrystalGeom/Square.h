#ifndef __SQUARE_H__
#define __SQUARE_H__

#include <vector>
#include "Point3d.h"
#include "Quaternion.h"

namespace Crystal {
	namespace Geom {
		

class Square
{
public:
	Square(const Geom::Point3d& center, const double length);

	~Square(void);

	Point3d getCenter() const { return center; }

	std::vector<Point3d> getPoints() const;

	std::vector<Point3d> getInnerPoints(const double divideLength) const;

	double getLength() const { return length; }

	double getArea() const { return length * length; }

private:
	const Point3d center;
	const Quaternion quaternion;
	const double length;
};

	}
}

#endif