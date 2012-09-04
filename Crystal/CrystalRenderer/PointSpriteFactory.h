#ifndef __POINT_SPRITE_FACTORY_H__
#define __POINT_SPRITE_FACTORY_H__

#include "PointSprite.h"

#include <vector>

namespace Crystal{
	namespace Renderer{

class PointSpriteFactory
{
public:
	PointSpriteFactory(unsigned int howMany) :
	  sprites(howMany)
	{
		for( unsigned int i = 0; i < howMany; ++i ) {
			sprites[i] = new PointSprite( i, Color4d() );
		}
	}

	  ~PointSpriteFactory()
	  {
		  for( unsigned int i = 0 ; i < sprites.size(); ++i ) {
			  delete sprites[i];
		  }
	  }


	std::vector<PointSprite*> getPointSprites() const { return sprites; }

private:
	std::vector<PointSprite*> sprites;
};

	}
}

#endif