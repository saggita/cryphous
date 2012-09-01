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
		 normal( 0.0, 0.0, 0.0)
		 {
		 }

	VisualParticle( const Crystal::Geom::Vector3d& center, double radius, const Crystal::Geom::Vector3d& normal) :
		 center( center),
		 radius( radius),
		 normal( normal)
		 {
		 }

	~VisualParticle(void){ }

public:
	Crystal::Geom::Vector3d center;
	Crystal::Geom::Vector3d normal;
	double radius;
};

typedef std::vector<VisualParticle> VisualParticleVector;

	}
}
#endif __VISUAL_PARTICLE_H__