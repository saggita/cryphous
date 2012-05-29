#include "Line.h"

using namespace Crystal::Geom;

bool Line::equals(const Line& rhs) const
{
	return (this->direction == rhs.getDirection()) &&
		(this->getStart() == rhs.getStart() );
}