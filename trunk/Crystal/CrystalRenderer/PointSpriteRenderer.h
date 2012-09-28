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

	void renderThickness(const PointSprite& sprite, const Point25d& center)
	{
		Point2d spritePoint( 0, 0);
		const size_t radius = sprite.getRadius();
		Point2d bufferPoint;
		for( bufferPoint.x = center.point.x - radius; bufferPoint.x <= center.point.x + radius; ++bufferPoint.x, ++spritePoint.x ) {
			for( bufferPoint.y = center.point.y - radius, spritePoint.y = 0; bufferPoint.y <= center.point.y + radius; ++bufferPoint.y, ++spritePoint.y ) {
				if( buffer.isValidPoint( bufferPoint) ) {
					const Color4d& spriteColor = sprite.getBuffer().getColor( spritePoint );
					buffer.addColor( bufferPoint, spriteColor );
				}
			}
		}
	}

	void renderSurface(const PointSprite& sprite, const Point25d& center)
	{
		Point2d spritePoint( 0, 0);
		const size_t radius = sprite.getRadius();
		Point2d bufferPoint;
		for( bufferPoint.x = center.point.x - radius; bufferPoint.x <= center.point.x + radius; ++bufferPoint.x, ++spritePoint.x ) {
			for( bufferPoint.y = center.point.y - radius, spritePoint.y = 0; bufferPoint.y <= center.point.y + radius; ++bufferPoint.y, ++spritePoint.y ) {
				if( buffer.isValidPoint( bufferPoint) ) {
					const Color4d& spriteColor = sprite.getBuffer().getColor( spritePoint );
					const Geom::Vector3d& spriteNormal = sprite.getBuffer().getNormal( spritePoint);
					const float spriteDepth = sprite.getBuffer().getDepth( spritePoint ) + center.depth;
					if( spriteDepth < buffer.getDepth( bufferPoint ) ) {
						buffer.setColor( bufferPoint, spriteColor );
						buffer.setDepth( bufferPoint, spriteDepth );
						buffer.setNormal( bufferPoint, spriteNormal );
					}
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