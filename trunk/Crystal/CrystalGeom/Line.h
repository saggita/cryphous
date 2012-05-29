#ifndef __LINE_H__
#define __LINE_H__

#include "Point3d.h"
#include "Vector3d.h"

#include <vector>
#include <list>

namespace Crystal{
	namespace Geom{

class Line
{
public:
	Line(void) :
	  origin(0.0, 0.0, 0.0),
	  direction( 1.0, 1.0, 1.0)
	  {};

	  Line( const Point3d& start, const Point3d& end ) :
	  origin( start),
	  direction( Vector3d(end) - Vector3d(start))
	  {}


	~Line(void){};

	Point3d getStart() const { return origin; }

	Point3d getEnd() const { return origin + direction; }

	Vector3d getDirection() const { return direction; }

	double getLength() const { return direction.getLength(); }

	bool equals(const Line& rhs) const;

private:
	Point3d origin;
	Vector3d direction;
};

static bool operator==(const Line& lhs, const Line& rhs){ return lhs.equals( rhs); }

static bool operator!=(const Line& lhs, const Line& rhs){ return !lhs.equals( rhs); }

typedef std::vector< Line > LineVector;
typedef std::list< Line > LineList;

	}
}

#endif