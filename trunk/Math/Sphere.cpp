#include "Sphere.h"

using namespace Crystal::Math;

std::vector<Vector3d> Sphere::createPoints(const float divideLength ) const
{
	std::vector<Vector3d> points;

	Box box( center, center );
	box.outerOffset( radius );

	for( float x = box.getMinX(); x <= box.getMaxX(); x+= divideLength ) {
		for( float y = box.getMinY(); y <= box.getMaxY(); y += divideLength ) {
			for( float z = box.getMinZ(); z <= box.getMaxZ(); z += divideLength ) {
				const Vector3d pos( x, y, z );
				if( pos.getDistanceSquared( center ) < radius * radius ) {
					points.push_back( pos );
				}
			}
		}
	}
	return points;
}