#ifndef __POINT_SPRITE_RENDERER_H__
#define __POINT_SPRITE_RENDERER_H__

#include "PointSprite.h"
#include "FrameBuffer.h"

namespace Crystal{
	namespace Renderer{

class PointSpriteRenderer
{
public:
	PointSpriteRenderer(FrameBuffer& buffer) :
	  buffer(buffer)
	{
	}

	/*void render(const PointSprite& sprite, const Point2d& center)
	{
		Point2d spritePoint( 0, 0);
		const int radius = sprite.getRadius();
		for( int x = center.x - radius; x <= center.x + radius; ++x ) {
			for( int y = center.y - radius; y <= center.y + radius; ++y ) {
				const Point2d bufferPoint(x,y);
				buffer.setColor( point, sprite.getBuffer().getColor( spritePoint ) );
				spritePoint.y ++
	
			}
				
		}
	}*/

private:
	FrameBuffer& buffer;
};

	}
}

#endif