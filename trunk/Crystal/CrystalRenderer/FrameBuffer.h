#ifndef __FRAME_BUFFER_H__
#define __FRAME_BUFFER_H__

#include "Color4d.h"

#include "../CrystalGeom/Vector3d.h"

#include <vector>

#include <iostream>

#include "Point2d.h"

#include "ColorBuffer.h"
#include "DepthBuffer.h"
#include "NormalBuffer.h"

namespace Crystal{
	namespace Renderer{

class FrameBuffer
{
public:
	FrameBuffer(const int xWidth, const int yWidth) :
	  colors( xWidth, yWidth),
		depths( xWidth, yWidth),
		normals( xWidth, yWidth)
	{
	}

	int getWidth() const { return colors.getWidth(); }

	int getHeight() const { return colors.getHeight(); }

	void setColor(const Point2d& point, const Color4d& color) { colors.setColor(point, color); }

	Color4d getColor(const Point2d& point) const { return colors.getColor( point); }

	void setNormal(const Point2d& point, const Geom::Vector3d& normal) { normals.setNormal( point, normal); }

	Geom::Vector3d getNormal(const Point2d& point) const { return normals.getNormal( point); }

	void setDepth(const Point2d& point, float depth) { depths.setDepth( point, depth ); }

	float getDepth(const Point2d& point) const { return depths.getDepth( point); }

	void clear(const Color4d& color) { colors.clear(color); }

	bool isValidPointX(const Point2d& point) { return (0 <= point.x) && (point.x < colors.getWidth() ); }

	bool isValidPointY(const Point2d& point) { return (0 <= point.y) && (point.y < colors.getHeight() ); }

	bool isInvalidPointX(const Point2d& point) { return !isValidPointX( point ); }

	bool isInvalidPointY(const Point2d& point) { return !isValidPointY( point ); }

	bool isValidPoint(const Point2d& point) { return isValidPointX( point ) && isValidPointY( point ); }

	bool isInvalidPoint(const Point2d& point) { return !isValidPoint( point ); }

private:
	ColorBuffer colors;
	NormalBuffer normals;
	DepthBuffer depths;
};

	}
}

#endif