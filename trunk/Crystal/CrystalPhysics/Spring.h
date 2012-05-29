#pragma once

namespace Crystal{
	namespace Geom {
		class Line;
	}
	namespace Physics{
		class Particle;

class Spring
{
public:

	Spring(Particle* particleX, Particle* particleY) : 
	  particleX( particleX), particleY( particleY)
	{};

	bool isEmpty() const { return (particleX == 0) || ( particleY == 0 ); }

	void enforce(const double restDistance, const double springCoefficient) const;

	Geom::Line getLine() const;

	Particle* getParticleX() const { return particleX; }

	Particle* getParticleY() const { return particleY; }

private:
	Particle* particleX;
	Particle* particleY;
};
	}
}
