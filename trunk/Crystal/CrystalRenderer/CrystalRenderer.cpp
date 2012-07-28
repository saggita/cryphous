#include <vector>

#include <iostream>

#include <cmath>

#include "ImageIO.h"

#include "Color4d.h"

namespace Crystal{
	namespace Renderer{

class Point
{
public:
	Point()
	{
	};
	Point(int x, int y, int z) :
		x(x), y(y), z(z)
	{
	};
	int x;
	int y;
	int z;
};

class Vector
{
public:
	Vector()
	{
	};
	Vector(signed char x, signed char y, signed char z) :
	x(x), y(y), z(z)
	{
	};
	signed char x;
	signed char y;
	signed char z;
};

class Bitmap
{
public:
	Bitmap(const int xWidth, const int yWidth)
	{
		colors.resize( xWidth );
		normals.resize( xWidth );
		for( int x = 0; x < xWidth; ++x ) {
			colors[x].resize( yWidth );
			normals[x].resize( yWidth );
			//depths[x].resize( yWidth );
			for( int y = 0; y < yWidth; ++y ) {
				colors[x][y] = Color4d( 0, 0, 0, 0 );
				normals[x][y] = Vector( 0, 0, 0);
			}
		}
	}

	Color4d getColor(size_t x, size_t y)
	{
		return colors[x][y];
	}

	Vector getNormal(size_t x, size_t y)
	{
		return normals[x][y];
	}

	void clear(const Color4d& color)
	{
		for( size_t x = 0; x < colors.size(); ++x ) {
			for( size_t y = 0; y < colors[x].size(); ++y ) {
				colors[x][y] = color;
			}
		}
	}

	void setNormal(const Point& point, const Vector& normal)
	{
		normals[point.x][point.y] = normal;
	}

	void setColor(const Point& point, const Color4d& color)
	{
		colors[point.x][point.y] += color;
	}

	void drawQuad(const Point& center, unsigned int radius, const Color4d& color)
	{
		for( unsigned int x = center.x- radius; x <= center.x+radius; ++x ){
			for( unsigned int y = center.y -radius; y<= center.y+radius; ++y) {
				setColor( Point(x, y, center.z), color );
			}
		}
	}

	void drawPoint(const Point& center, unsigned int radius, const Color4d& color)
	{
		unsigned int radiusSquared = radius * radius;
		for( unsigned int x = center.x- radius; x <= center.x+radius; ++x ){
			for( unsigned int y = center.y -radius; y<= center.y+radius; ++y) {
				const Vector normal( x - center.x, y - center.y, 0.0);
				const double lengthSquared = (x - center.x) * (x - center.x) + (y - center.y) * (y - center.y);
				if( lengthSquared < radiusSquared ) {
					setColor( Point(x, y, center.z), color );
					setNormal( Point(x, y, center.z), normal );
				}
			}
		}
	}

	void dump()
	{
		for( size_t x = 0; x < colors.size(); ++x ) {
			for( size_t y = 0; y < colors[x].size(); ++y ) {
				std::cout << colors[x][y].red << colors[x][y].green << colors[x][y].blue << " ";
			}
			std::cout << std::endl;
		}
	}

private:
	std::vector< std::vector<Color4d> > colors;
	std::vector< std::vector<float> > depths;
	std::vector< std::vector<Vector> > normals;
};

	}
}

