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
	Color4d(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha = 255) :
	  red(red), green(green), blue(blue), alpha(alpha)
	{
	};
	unsigned char red;
	unsigned char green;
	unsigned char blue;
	unsigned char alpha;

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