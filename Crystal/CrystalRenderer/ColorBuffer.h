#ifndef __COLOR_BUFFER_H__
#define __COLOR_BUFFER_H__

#include "Color4d.h"

#include <vector>

namespace Crystal{
	namespace Renderer{

class ColorBuffer
{
public:
	ColorBuffer(const int xWidth, const int yWidth)
	{
		colors.resize( xWidth );
		for( int x = 0; x < xWidth; ++x ) {
			colors[x].resize( yWidth );
			for( int y = 0; y < yWidth; ++y ) {
				colors[x][y] = Color4d( 0, 0, 0, 0 );
			}
		}
	}

	int getWidth() const { return colors.size(); }

	int getHeight() const { return colors[0].size(); }

	Color4d getColor(size_t x, size_t y)
	{
		return colors[x][y];
	}

	void clear(const Color4d& color)
	{
		for( size_t x = 0; x < colors.size(); ++x ) {
			for( size_t y = 0; y < colors[x].size(); ++y ) {
				colors[x][y] = color;
			}
		}
	}

	void setColor(const Point2d& point, const Color4d& color)
	{
		colors[point.x][point.y] = color;
	}

	/*void drawPoint(const Point3d& center, unsigned int radius, const Color4d& color)
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

private:
	std::vector< std::vector<Color4d> > colors;
};

	}
}

#endif