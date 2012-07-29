#ifndef __PIXEL_MAP_H__
#define __PIXEL_MAP_H__

#include "Color4d.h"

#include "../CrystalGeom/Vector3d.h"

#include <vector>

#include <iostream>

#include "Point2d.h"

#include "ColorBuffer.h"
#include "NormalBuffer.h"

namespace Crystal{
	namespace Renderer{

class FrameBuffer
{
public:
	FrameBuffer(const int xWidth, const int yWidth) :
	  colors( xWidth, yWidth),
		normals( xWidth, yWidth)
	{
	}

	int getWidth() const { return colors.getWidth(); }

	int getHeight() const { return colors.getHeight(); }

	Color4d getColor(size_t x, size_t y)
	{
		return colors.getColor(x,y);
	}

	Geom::Vector3d getNormal(size_t x, size_t y)
	{
		return normals.getNormal(x,y);
	}

	void clear(const Color4d& color)
	{
		colors.clear(color);
	}

	void setNormal(const Point2d& point, const Geom::Vector3d& normal)
	{
		normals.setNormal( point, normal);
	}

	void setColor(const Point2d& point, const Color4d& color)
	{
		colors.setColor(point, color);
	}

	/*void drawQuad(const Point3d& center, unsigned int radius, const Color4d& color)
	{
		for( unsigned int x = center.x- radius; x <= center.x+radius; ++x ){
			for( unsigned int y = center.y -radius; y<= center.y+radius; ++y) {
				setColor( Point3d(x, y, center.z), color );
			}
		}
	}

	void drawPoint(const Point3d& center, unsigned int radius, const Color4d& color)
	{
		unsigned int radiusSquared = radius * radius;
		for( unsigned int x = center.x- radius; x <= center.x+radius; ++x ){
			for( unsigned int y = center.y -radius; y<= center.y+radius; ++y) {
				const Geom::Vector3d normal( x - center.x, y - center.y, 0);
				if( normal.getLengthSquared() < radiusSquared ) {
					setColor( Point3d(x, y, center.z), color );
					setNormal( Point3d(x, y, center.z), normal );
				}
			}
		}
	}*/

	/*void dump()
	{
		for( size_t x = 0; x < colors.size(); ++x ) {
			for( size_t y = 0; y < colors[x].size(); ++y ) {
				std::cout << colors[x][y].red << colors[x][y].green << colors[x][y].blue << " ";
			}
			std::cout << std::endl;
		}
	}*/

private:
	ColorBuffer colors;
	NormalBuffer normals;
	std::vector< std::vector<float> > depths;
	//std::vector< std::vector<Geom::Vector3d> > normals;
};

	}
}

#endif