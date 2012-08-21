#ifndef __SHADER_PARTICLE_H__
#define __SHADER_PARTICLE_H__

#include "../CrystalGeom/Vector3d.h"
#include <list>

namespace Crystal{
	namespace Shader{

class ShaderParticle
{
public:
	ShaderParticle(void) :
	  center( 0.0, 0.0, 0.0),
		velocity( 0.0, 0.0, 0.0 ),
		radius(1.0),
		color(1.0, 1.0, 1.0, 1.0),
		age(0)
	  {};

	 ShaderParticle(  const Geom::Vector3d& center, double radius, const Geom::Vector3d& velocity, const Color::ColorRGBA<>& color, int age ) :
	  center( center),
		  radius(radius),
		  velocity( velocity),
		  color(color),
		  age(age)
	 {};
	  
	~ShaderParticle(void)
	{};

public:
	Geom::Vector3d center;
	Geom::Vector3d velocity;
	Color::ColorRGBA<> color;
	double radius;
	int age;
};

typedef std::list<ShaderParticle> ShaderParticleList;

	}
}
#endif