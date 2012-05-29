#pragma once

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
