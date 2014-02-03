#ifndef __CRYSTAL_SHADER_VISUAL_PARTICLE_H__
#define __CRYSTAL_SHADER_VISUAL_PARTICLE_H__

#include <vector>

#include "../Math/Vector3d.h"

namespace Crystal{
	namespace Shader{

class VisualParticle
{
public:
	Math::Vector3d center;
	float density;
};

typedef std::vector<VisualParticle> VisualParticleVector;

	}
}
#endif