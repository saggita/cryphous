#ifndef __COLOR_4D__
#define __COLOR_4D__

namespace Crystal{
	namespace Renderer{

class Color4d
{
public:
	Color4d()
	{
	};
	Color4d(float red, float green, float blue, float alpha = 1.0) :
	  red(red), green(green), blue(blue), alpha(alpha)
	{
	};
	float red;
	float green;
	float blue;
	float alpha;

	void operator+=(const Color4d& rhs)
	{
		red += rhs.red;
		green += rhs.green;
		blue += rhs.blue;
		alpha += rhs.alpha;
	}

	bool operator==(const Color4d& rhs)
	{
		return (red == rhs.red) && (green == rhs.green) && (blue == rhs.blue) && (alpha == rhs.alpha);
	}

	bool operator!=(const Color4d& rhs)
	{
		return !operator==(rhs);
	}
};

	}
}

#endif