
#include "Primitive.h"

#include <cmath>
#include <algorithm>

using namespace Crystal::Geom;

Primitive::Primitive(const Point3d& pointX, const Point3d& pointY, const Type type) :
center( (pointX.getX() + pointY.getX()) * 0.5,
	   (pointX.getY() + pointY.getY()) * 0.5,
	   (pointX.getZ() + pointY.getZ()) * 0.5 ),
minX( std::min( pointX.getX(), pointY.getX() )),
maxX( std::max( pointX.getX(), pointY.getX() )),
minY( std::min( pointX.getY(), pointY.getY() )),
maxY( std::max( pointX.getY(), pointY.getY() )),
minZ( std::min( pointX.getZ(), pointY.getZ() )),
maxZ( std::max( pointX.getZ(), pointY.getZ() )),
type( type )
{
	minX -= center.getX();
	maxX -= center.getX();
	minY -= center.getY();
	maxY -= center.getY();
	minZ -= center.getZ();
	maxZ -= center.getZ();
}
