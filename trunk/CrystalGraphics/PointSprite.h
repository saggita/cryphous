#ifndef __POINT_SPRITE_H__
#define __POINT_SPRITE_H__

namespace Crystal{
	namespace Graphics{

class PointSprite
{
public:
	PointSprite(void);

	~PointSprite(void);

	void apply();

	void release();

	static PointSprite* get() {
		static PointSprite pointSprite;
		return &pointSprite;
	}
};

	}
}

#endif