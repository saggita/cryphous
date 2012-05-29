#pragma once

#include <vector>

namespace Crystal{
	namespace Physics{
		class Particle;
		typedef std::vector<Particle*> ParticleVector;
	}
	namespace Graphics{

class VisualObjects
{
public:
	VisualObjects() {};

	~VisualObjects(void){};

	void drawParticles(const Physics::ParticleVector& particles);

	void drawSprings();
};

	}
}