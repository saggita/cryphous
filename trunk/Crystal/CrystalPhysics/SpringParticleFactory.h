#ifndef __SPRING_PARTICLE_FACTORY_H__
#define __SPRING_PARTICLE_FACTORY_H__

#include <list>
#include <vector>

namespace Crystal{
	namespace Geom{
		class Line;
		typedef std::list<Line> LineList;
	}

	namespace Physics{
		class Particle;
		typedef std::vector<Particle*> ParticleVector;
		class SpringParticle;
		typedef std::list<SpringParticle*> SpringParticleList;
		typedef std::vector< std::vector< std::vector< Particle* > > > ParticleGrid;

class SpringParticleFactory
{
public:
	SpringParticleFactory(const ParticleVector& particles, const int uNumber, const int vNumber, const int wNumber);

	~SpringParticleFactory(void);

	void createSpringParticles(const ParticleVector& particles);

	SpringParticleList getSpringParticles() const { return springParticles; }

	Geom::LineList getLines() const;

	ParticleGrid getParticleGrid() const { return particleGrid; }

	std::vector<Particle*> getCorners() const;

protected:
	SpringParticleList springParticles;
	ParticleGrid particleGrid;
	const int uNumber;
	const int vNumber;
	const int wNumber;
};

	}
}

#endif