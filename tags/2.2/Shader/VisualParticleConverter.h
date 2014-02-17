#include <vector>

#include "VisualParticle.h"

namespace Crystal{
	namespace Shader{

class VisualParticleConverter{
public:
	static std::vector<float> toPositionArray(const VisualParticleVector& particles);

	static std::vector<float> toDensityArray(const VisualParticleVector& particles);

	static std::vector<float> toColorArray(const VisualParticleVector& particles);

private:
	static std::vector<float> toPositionArray(const VisualParticle& particle);

	static std::vector<float> toColorArray(const VisualParticle& particle);
};

	}
}