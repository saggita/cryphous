#ifndef __PARTICLE_CONDITIONS_H__
#define __PARTICLE_CONDITIONS_H__

#include <vector>

namespace Cryphous{
	namespace Physics{

class ParticleConditions
{
public:

	ParticleConditions();

	ParticleConditions(const float particleLength, const float density, const float pressureCoe, const float viscosityCoe) :
		particleLength( particleLength),
		 density( density),
		 pressureCoe( pressureCoe),
		 viscosityCoe( viscosityCoe)
		{
		}

	float getParticleLength() const { return particleLength; }

	float getDensity() const { return density; }

	float getParticleVolume() const { return particleLength * particleLength * particleLength; }

	float getParticleMass() const { return density * getParticleVolume(); }

	float getPressureCoe() const { return pressureCoe; }

	float getViscosityCoe() const { return viscosityCoe; }

public:
	float particleLength;
	float density;
	float pressureCoe;
	float viscosityCoe;
};

	}
}

#endif