#ifndef __POINT_2D_H__
#define __POINT_2D_H__

namespace Crystal{
	namespace Renderer{

struct Point2d
{
public:
	Point2d()
	{
	}
	Point2d(int x, int y) :
	x(x), y(y)
	{
	}
	int x;
	int y;
};
	}
}

#endif