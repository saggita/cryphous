#ifndef __LOOP_H__
#define __LOOP_H__

#include <vector>

namespace Crystal{
	namespace Geom{
		class Line;
		typedef std::vector< Line > LineVector;
		class Point3d;
		typedef std::vector< Point3d > PointVector;

class Loop
{
public:

	Loop( const PointVector& points );

	~Loop(void);

	void create( const PointVector& points );

	bool isValid() const;

	bool isClosed() const;

	bool isOpen() const;

	LineVector getLines() const;

	PointVector getPoints() const { return points; }

	void close();

	void open();

private:
	PointVector points;
};
	}
}

#endif