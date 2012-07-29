#ifndef __DEPTH_BUFFER_H__
#define __DEPTH_BUFFER_H__

#include "../CrystalGeom/Vector3d.h"

#include <vector>

namespace Crystal{
	namespace Renderer{

class NormalBuffer
{
public:
	NormalBuffer(const int xWidth, const int yWidth)
	{
		normals.resize( xWidth );
		for( int x = 0; x < xWidth; ++x ) {
			normals[x].resize( yWidth );
			for( int y = 0; y < yWidth; ++y ) {
				normals[x][y] = Geom::Vector3d( 0.0, 0.0, 0.0);
			}
		}
	}

	int getWidth() const { return normals.size(); }

	int getHeight() const { return normals[0].size(); }

	Geom::Vector3d getNormal(unsigned int x, unsigned int y)
	{
		return normals[x][y];
	}

	void clear(const Geom::Vector3d& normal)
	{
		for( size_t x = 0; x < normals.size(); ++x ) {
			for( size_t y = 0; y < normals[x].size(); ++y ) {
				normals[x][y] = normal;
			}
		}
	}

	void setNormal(const Point2d& point, const Geom::Vector3d& normal)
	{
		normals[point.x][point.y] = normal;
	}


private:
	std::vector< std::vector<Geom::Vector3d> > normals;
};

	}
}

#endif