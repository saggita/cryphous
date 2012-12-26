#ifndef __VISUAL_PARTICLE_H__
#define __VISUAL_PARTICLE_H__

#include <list>

#include "../CrystalGeom/Vector3d.h"

namespace Amorphous{
	namespace Shader{

class VisualParticle
{
public:

	VisualParticle() :
		 center( Crystal::Geom::Vector3d(0.0f, 0.0f, 0.0f) ),
		 radius( 1.0)
		 {
		 }

	VisualParticle( const Crystal::Geom::Vector3d& center, double radius) :
		 center( center),
		 radius( radius)
		 {
		 }

	~VisualParticle(void){ }

public:
	Crystal::Geom::Vector3d center;
	double radius;
};

typedef std::list<VisualParticle> VisualParticleList;

	}
}
#endif __VISUAL_PARTICLE_H__