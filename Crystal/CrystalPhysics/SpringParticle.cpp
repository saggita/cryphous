#include "SpringParticle.h"

#include "../CrystalGeom/Line.h"

#include <boost/foreach.hpp>

using namespace Crystal::Geom;
using namespace Crystal::Physics;

SpringParticle::~SpringParticle()
{
}

bool SpringParticle::isBoundary() const
{
	BOOST_FOREACH( const Spring& spring, springs ) {
		if( spring.isEmpty() ){
			return true;
		}
	}
	return false;
}

void SpringParticle::enforce(const double restDistance, const double springCoefficient)
{
	BOOST_FOREACH( const Spring& spring, springs ) {
		spring.enforce( restDistance, springCoefficient );
	}
}

LineList SpringParticle::getLines() const
{
	LineList lines;
	BOOST_FOREACH( const Spring& spring, springs ) {
		if( spring.isEmpty() ) {
			continue;
		}
		lines.push_back( spring.getLine() );
	}
	return lines;
}