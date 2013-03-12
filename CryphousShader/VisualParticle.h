#ifndef __CRYPHOUS_VISUAL_PARTICLE_H__
#define __CRYPHOUS_VISUAL_PARTICLE_H__

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
	float density;
};

typedef std::list<VisualParticle> VisualParticleList;

class VisualParticleCollection
{
public:

	VisualParticleCollection(){};

	VisualParticleCollection(const VisualParticleList& vpl)
	{
		set( vpl );
	}

	void set(const VisualParticleList& vpl)
	{
		centers.clear();
		densities.clear();
		for( const VisualParticle& vp: vpl ) {
			centers.push_back( vp.center.x );
			centers.push_back( vp.center.y );
			centers.push_back( vp.center.z );
			densities.push_back( vp.density );
		}
	}

public:
	std::vector<double> centers;
	std::vector<double> densities;
};

	}
}
#endif