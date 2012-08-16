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

	void render(const PointSprite& sprite, const Point2d& center)
	{
		Point2d spritePoint( 0, 0);
		const int radius = sprite.getRadius();
		Point2d bufferPoint;
		for( bufferPoint.x = center.x - radius; bufferPoint.x < center.x + radius; ++bufferPoint.x, ++spritePoint.x ) {
			for( bufferPoint.y = center.y - radius, spritePoint.y = 0; bufferPoint.y < center.y + radius; ++bufferPoint.y, ++spritePoint.y ) {
				if( buffer.isValidPoint( bufferPoint) ) {
					const Color4d& spriteColor = sprite.getBuffer().getColor( spritePoint );
					buffer.setColor( bufferPoint, spriteColor );
				}
			}
		}
	}

private:
	FrameBuffer& buffer;
};

	}
}

#endif