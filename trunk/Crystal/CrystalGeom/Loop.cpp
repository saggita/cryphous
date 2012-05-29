#include "Loop.h"
#include "Line.h"

#include <cassert>

using namespace Crystal::Geom;


Loop::Loop( const PointVector& points ) :
points( points )
{
	assert( !points.empty() );
}

Loop::~Loop(void)
{
}

bool Loop::isValid() const
{
	return !points.empty();
}

bool Loop::isClosed() const
{
	assert( isValid() );
	return ( points.front() == points.back() );
}

bool Loop::isOpen() const
{
	assert( isValid() );
	return !isClosed();
}

LineVector Loop::getLines() const
{
	assert( isValid() );
	LineVector lines;
	for( size_t i = 1; i < points.size(); ++i ) {
		lines.push_back( Line( points[i-1], points[i] ) );
	}
	return lines;
}

void Loop::close()
{
	assert( isOpen() );
	points.push_back( points.front() );
	assert( isClosed() );
}

void Loop::open()
{
	assert( isClosed() );
	points.pop_back();
	assert( isOpen() );
}