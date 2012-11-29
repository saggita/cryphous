#ifndef __VISUAL_PARTICLE_H__
#define __VISUAL_PARTICLE_H__

#include <list>

#include "../AmorphousGeom/Vector3d.h"

namespace Amorphous{
	namespace Color{

class VisualParticle
{
public:

	VisualParticle() :
		 center( Geom::Vector3d<>(0.0, 0.0, 0.0) ),
		 temperature( 300.0 ),
		 radius( 1.0)
		 {
		 }

	VisualParticle( const Geom::Vector3d<>& center, double temperature, double radius, const Geom::Vector3d<>& velocity) :
		 center( center),
		 temperature( temperature),
		 radius( radius)
		 {
		 }

	~VisualParticle(void){ }

public:
	Geom::Vector3d<> center;
	double temperature;
	double radius;
};

typedef std::list<VisualParticle> VisualParticleList;

	}
}
#endif __VISUAL_PARTICLE_H__