#ifndef __VISUAL_PARTICLE_H__
#define __VISUAL_PARTICLE_H__

#include <list>

#include "../CrystalGeom/Vector3d.h"

namespace Crystal{
	namespace Shader{

class VisualParticle
{
public:

	VisualParticle() :
		 center( Crystal::Geom::Vector3d(0.0f, 0.0f, 0.0f) )
		 {
		 }

	VisualParticle( const Crystal::Geom::Vector3d& center) :
		 center( center)
		 {
		 }

	~VisualParticle(void){ }

public:
	Crystal::Geom::Vector3d center;
};

typedef std::list<VisualParticle> VisualParticleList;

	}
}
#endif __VISUAL_PARTICLE_H__