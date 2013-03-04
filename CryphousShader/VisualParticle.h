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
		 center( Cryphous::Geometry::Vector3d(0.0f, 0.0f, 0.0f) ),
		 density( 1000.0)
		 {
		 }

	VisualParticle( const Cryphous::Geometry::Vector3d& center) :
		 center( center),
		 density( 1000.0)
		 {
		 }

	VisualParticle( const Cryphous::Geometry::Vector3d& center, const float density) :
		 center( center),
		 density( density)
		 {
		 }

	~VisualParticle(void){ }

public:
	Cryphous::Geometry::Vector3d center;
	//std::vector<float> centers;
	float density;
};

typedef std::list<VisualParticle> VisualParticleList;

	}
}
#endif __VISUAL_PARTICLE_H__