#ifndef __POINT_SPRITE_H__
#define __POINT_SPRITE_H__

#include "Color4d.h"

#include "ColorBuffer.h"

#include <vector>

namespace Crystal{
	namespace Renderer{

class PointSprite
{
public:
	PointSprite(unsigned int radius)
	{
		ColorBuffer colorBuffer( radius * 2, radius * 2 );
		for( int x = 0; x < colorBuffer.getWidth(), ++x ) {
			colors.push_back( std::vector<Color4d>() );
			for( int y = 0; y < colorBuffer.getWidth(); ++y ) {
				colorsBuffer[x][y].setColor( 0, 0, 0, 255 );
			}
		}
	}
	private:
		ColorBuffer colorBuffer;
	
	}
};

	}
}

#endif