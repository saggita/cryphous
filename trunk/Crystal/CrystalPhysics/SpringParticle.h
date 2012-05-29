#ifndef __SPRING_PARTICLE_H__
#define __SPRING_PARTICLE_H__

#include "Spring.h"
#include <vector>
#include <list>

namespace Crystal{
	namespace Geom{
		class Line;
		typedef std::list<Line> LineList;
	}
	namespace Physics{
		class Particle;

class SpringParticle
{
public:
	SpringParticle(Particle* center, Particle* uPlus, Particle* vPlus, Particle* wPlus )
	{
		springs.push_back( Spring( center, uPlus ) );
		springs.push_back( Spring( center, vPlus ) );
		springs.push_back( Spring( center, wPlus ) );
	}

	~SpringParticle();

	bool isBoundary() const;

	void enforce(const double restDistance, const double springCoefficient);

	Geom::LineList getLines() const;

private:
	std::vector<Spring> springs;
};

typedef std::list<SpringParticle*> SpringParticleList;
typedef std::vector<SpringParticle*> SpringParticleVector;

	}
}

#endif



