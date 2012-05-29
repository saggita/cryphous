
#include "ParticleConditions.h"

#include "../CrystalGeom/Point3d.h"
#include "../CrystalGeom/Box.h"
#include "../CrystalGeom/Tolerances.h"

#include <cassert>

using namespace Crystal::Geom;
using namespace Crystal::Physics;

void ParticleConditions::createInnerPoints()
{
	assert( innerPoints.empty() );

	const double margin = 1.0e-12;

	Point3d max = box.getMax();
	max -= Point3d( particleLength * 0.5, particleLength * 0.5, particleLength * 0.5 );
	max += Point3d( margin, margin, margin );
	Point3d min = box.getMin();
	min += Point3d( particleLength * 0.5, particleLength * 0.5, particleLength * 0.5 );
	min -= Point3d( margin, margin, margin );

	for( double x = min.getX(); x < max.getX(); x += particleLength ) {
		this->xNumber++;
	}
	for( double y = min.getY(); y < max.getY(); y += particleLength ) {
		this->yNumber++;
	}
	for( double z = min.getZ(); z < max.getZ(); z += particleLength ) {
		this->zNumber++;
	}

	for( double x = min.getX(); x < max.getX(); x += particleLength ) {
		for( double y = min.getY(); y < max.getY(); y += particleLength ) {
			for( double z = min.getZ(); z < max.getZ(); z += particleLength ) {
				innerPoints.push_back( Point3d( x, y, z ) );
			}
		}
	}
}