#ifndef __DEPTH_SPRITE_RENDERER_H__
#define __DEPTH_SPRITE_RENDERER_H__

#include "OffScreenRendererBase.h"
#include "VisualParticle.h"
#include <memory>

namespace Crystal{
	namespace Shader{

class VisualParticleCollection;
class RenderingCommandStack;
class ShaderCommandStack;

class DepthRenderer : public OffScreenRendererBase
{
public:
	DepthRenderer(const float& size);

	~DepthRenderer(void);

	//void setVisualParticles(const VisualParticleVector& particles);

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

	const float& size;
};

	}
}
#endif