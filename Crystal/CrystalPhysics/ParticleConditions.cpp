
#include "ParticleConditions.h"

#include "../CrystalGeom/Vector3d.h"
#include "../CrystalGeom/Box.h"
#include "../CrystalGeom/Tolerances.h"

#include <cassert>

using namespace Crystal::Geom;
using namespace Crystal::Physics;

void ParticleConditions::createInnerPoints(const Box& box)
{
	assert( innerPoints.empty() );

	const double margin = 1.0e-12;

	Vector3d max = box.getMax();
	max -= Vector3d( particleLength * 0.5, particleLength * 0.5, particleLength * 0.5 );
	max += Vector3d( margin, margin, margin );
	Vector3d min = box.getMin();
	min += Vector3d( particleLength * 0.5, particleLength * 0.5, particleLength * 0.5 );
	min -= Vector3d( margin, margin, margin );

	for( double x = min.getX(); x < max.getX(); x += particleLength ) {
		for( double y = min.getY(); y < max.getY(); y += particleLength ) {
			for( double z = min.getZ(); z < max.getZ(); z += particleLength ) {
				innerPoints.push_back( Vector3d( x, y, z ) );
			}
		}
	}
}