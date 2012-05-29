#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include <vector>

namespace Crystal{
	namespace Geom{

		class Point3d;
		typedef std::vector<Point3d> PointVector;
		class Line;
		typedef std::vector<Line> LineVector;
		class Vector3d;

class Triangle
{
public:
	Triangle(const PointVector& points);

	Triangle(const Point3d& pointX, const Point3d& pointY, const Point3d& pointZ);
	
	~Triangle(void){};

	LineVector getLines() const;

	PointVector getPoints() const { return points; }

	Vector3d getNormal() const;

	double getArea() const;

private:
	PointVector points;
};

	}
}

#endif