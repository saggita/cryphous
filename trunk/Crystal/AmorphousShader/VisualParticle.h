#ifndef __VISUAL_PARTICLE_H__
#define __VISUAL_PARTICLE_H__

#include <vector>

#include "../CrystalGeom/Vector3d.h"

namespace Crystal{
	namespace Shader{

class VisualParticle
{
public:

	VisualParticle() :
		 center( Crystal::Geom::Vector3d(0.0f, 0.0f, 0.0f) ),
		 radius( 1.0),
		 velocity( 0.0, 0.0, 0.0)
		 {
		 }

	VisualParticle( const Crystal::Geom::Vector3d& center, double radius, const Crystal::Geom::Vector3d& velocity) :
		 center( center),
		 radius( radius),
		 velocity( velocity)
		 {
		 }

	~VisualParticle(void){ }

public:
	Crystal::Geom::Vector3d center;
	Crystal::Geom::Vector3d velocity;
	double radius;
};

typedef std::vector<VisualParticle> VisualParticleVector;

	}
}
#endif __VISUAL_PARTICLE_H__