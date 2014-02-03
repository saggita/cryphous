#ifndef __CRYSTAL_GRAPHICS_THICKNESS_RENDERER_H__
#define __CRYSTAL_GRAPHICS_THICKNESS_RENDERER_H__

#include "OffScreenRendererBase.h"
#include "VisualParticle.h"
#include <memory>

namespace Crystal{
	namespace Shader{

		class RenderingCommandStack;
		class ShaderCommandStack;

class ThicknessRenderer : public OffScreenRendererBase
{
public:
	ThicknessRenderer(float& size, float& alpha);

	~ThicknessRenderer(void);

	void setVisualParticles(const std::vector<float>& positions, const std::vector<float>& densities) {
		this->positions = positions;
		this->densities = densities;
	}


protected:
	virtual void onRender();

	void onRender(RenderingCommandStack& commands, ShaderCommandStack& sCommands);

	virtual void onInit();

	virtual void onIdle(){};

private:
	std::vector<float> positions;
	std::vector<float> densities;

	float& size;
	float& alpha;
};

	}
}
#endif