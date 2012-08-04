#ifndef __COLOR_BUFFER_H__
#define __COLOR_BUFFER_H__

#include "Point2d.h"
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
				colors[x][y] = Color4d( 0.0, 0.0, 0.0 );
			}
		}
	}

	int getWidth() const { return colors.size(); }

	int getHeight() const { return colors[0].size(); }

	void clear(const Color4d& color)
	{
		for( size_t x = 0; x < colors.size(); ++x ) {
			for( size_t y = 0; y < colors[x].size(); ++y ) {
				colors[x][y] = color;
			}
		}
	}

	Color4d getColor(const Point2d& point) const
	{
		return colors[point.x][point.y];
	}

	void setColor(const Point2d& point, const Color4d& color)
	{
		colors[point.x][point.y] = color;
	}

private:
	std::vector< std::vector<Color4d> > colors;
};

	}
}

#endif