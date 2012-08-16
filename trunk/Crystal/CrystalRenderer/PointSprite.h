#ifndef __POINT_SPRITE_H__
#define __POINT_SPRITE_H__

#include "Color4d.h"
#include "Point2d.h"
#include "../CrystalGeom/Vector3d.h"

#include "FrameBuffer.h"

#include <vector>

namespace Crystal{
	namespace Renderer{

class PointSprite
{
public:
	PointSprite(unsigned int radius, const Color4d& color) :
	  buffer( radius * 2 + 1, radius * 2 + 1)
	{
		for( int x = 0; x <= buffer.getWidth(); ++x ) {
			for( int y = 0; y <= buffer.getHeight(); ++y ) {
				const int diffX = x-radius;
				const int diffY = y-radius;
				const unsigned int lengthSquared = diffX * diffX + diffY * diffY;
				if( lengthSquared > radius * radius ) {
					continue;
				}
				const float depth = std::sqrt( radius * radius - static_cast<float>(lengthSquared) );
				Geom::Vector3d normal( static_cast<float>(diffX), static_cast<float>(diffY), depth );
				normal.normalize();
				buffer.setNormal( Point2d(x,y), normal );
				buffer.setDepth( Point2d(x,y), depth );
				buffer.setColor( Point2d(x,y), color );
			}
		}
	}

	const FrameBuffer& getBuffer() const { return buffer; }

	const int getRadius() const { return buffer.getWidth() / 2; }

private:
	FrameBuffer buffer;
};

	}
}

#endif