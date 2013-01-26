#ifndef __VISUAL_PARTICLE_H__
#define __VISUAL_PARTICLE_H__

#include <list>

#include "../CryphousGeometry/Vector3d.h"

namespace Cryphous{
	namespace Shader{

class VisualParticle
{
public:

	VisualParticle() :
		 center( Cryphous::Geometry::Vector3d(0.0f, 0.0f, 0.0f) )
		 {
		 }

	VisualParticle( const Cryphous::Geometry::Vector3d& center) :
		 center( center)
		 {
		 }

	~VisualParticle(void){ }

public:
	Cryphous::Geometry::Vector3d center;
};

typedef std::list<VisualParticle> VisualParticleList;

	}
}
#endif __VISUAL_PARTICLE_H__