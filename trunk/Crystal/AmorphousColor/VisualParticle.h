#ifndef __VISUAL_PARTICLE_H__
#define __VISUAL_PARTICLE_H__

#include <list>

#include "../CrystalGeom/Vector3d.h"

namespace Crystal{
	namespace Color{

class VisualParticle
{
public:

	VisualParticle() :
		 center( Crystal::Geom::Vector3d(0.0f, 0.0f, 0.0f) ),
		 temperature( 300.0 ),
		 radius( 1.0),
		 velocity( 0.0, 0.0, 0.0)
		 {
		 }

	VisualParticle( const Crystal::Geom::Vector3d& center, double temperature, double radius, const Crystal::Geom::Vector3d& velocity) :
		 center( center),
		 temperature( temperature),
		 radius( radius),
		 velocity( velocity)
		 {
		 }

	~VisualParticle(void){ }

public:
	Crystal::Geom::Vector3d center;
	Crystal::Geom::Vector3d velocity;
	double temperature;
	double radius;
};

typedef std::list<VisualParticle> VisualParticleList;

	}
}
#endif __VISUAL_PARTICLE_H__