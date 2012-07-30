#ifndef __POINT_SPRITE_H__
#define __POINT_SPRITE_H__

#include "Color4d.h"
#include "Point2d.h"

#include "ColorBuffer.h"

#include <vector>

namespace Crystal{
	namespace Renderer{

class PointSprite
{
public:
	PointSprite(unsigned int radius) :
	  colors( radius * 2, radius * 2)
	{
		ColorBuffer colors( radius * 2, radius * 2 );
		for( int x = 0; x < colors.getWidth(); ++x ) {
			for( int y = 0; y < colors.getWidth(); ++y ) {
				colors.setColor( Point2d(x,y), Color4d( 0, 0, 0, 255 ) );
			}
		}
	}
private:
	ColorBuffer colors;
};

	}
}

#endif