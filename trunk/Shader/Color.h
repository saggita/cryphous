#ifndef __CRYSTAL_GRAPHICS_COLOR_H__
#define __CRYSTAL_GRAPHICS_COLOR_H__

namespace Crystal{
	namespace Shader{

class Color{
public:
	float red;
	float green;
	float blue;
	float alpha;

	Color()
	{}

	Color(float red, float green, float blue, float alpha) :
		red( red ), green( green ), blue( blue ), alpha( alpha )
	{}

	static Color Black() {
		Color color;
		color.red = 0.0;
		color.green = 0.0;
		color.blue = 0.0;
		color.alpha = 0.0;
		return color;
	}
};
	}
}

#endif