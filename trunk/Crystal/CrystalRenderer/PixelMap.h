#ifndef __PIXEL_MAP_H__
#define __PIXEL_MAP_H__

#include "Color4d.h"

#include "../CrystalGeom/Vector3d.h"

#include <vector>

#include <iostream>

namespace Crystal{
	namespace Renderer{

struct Point3d
{
public:
	Point3d()
	{
	}
	Point3d(int x, int y, int z) :
	x(x), y(y), z(z)
	{
	}
	int x;
	int y;
	int z;
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
				normals[x][y] = Geom::Vector3d( 0, 0, 0);
			}
		}
	}

	int getWidth() const { return colors.size(); }

	int getHeight() const { return colors[0].size(); }

	Color4d getColor(size_t x, size_t y)
	{
		return colors[x][y];
	}

	Geom::Vector3d getNormal(size_t x, size_t y)
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

	void setNormal(const Point3d& point, const Geom::Vector3d& normal)
	{
		normals[point.x][point.y] = normal;
	}

	void setColor(const Point3d& point, const Color4d& color)
	{
		colors[point.x][point.y] += color;
	}

	void drawQuad(const Point3d& center, unsigned int radius, const Color4d& color)
	{
		for( unsigned int x = center.x- radius; x <= center.x+radius; ++x ){
			for( unsigned int y = center.y -radius; y<= center.y+radius; ++y) {
				setColor( Point3d(x, y, center.z), color );
			}
		}
	}

	void drawPoint(const Point3d& center, unsigned int radius, const Color4d& color)
	{
		unsigned int radiusSquared = radius * radius;
		for( unsigned int x = center.x- radius; x <= center.x+radius; ++x ){
			for( unsigned int y = center.y -radius; y<= center.y+radius; ++y) {
				const Geom::Vector3d normal( x - center.x, y - center.y, 0);
				if( normal.getLengthSquared() < radiusSquared ) {
					setColor( Point3d(x, y, center.z), color );
					setNormal( Point3d(x, y, center.z), normal );
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
	std::vector< std::vector<Geom::Vector3d> > normals;
};

	}
}

#endif