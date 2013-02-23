#ifndef __DEPTH_SPRITE_RENDERER_H__
#define __DEPTH_SPRITE_RENDERER_H__

#include "OffScreenRendererBase.h"
#include "VisualParticle.h"
#include <memory>

namespace Cryphous{
	namespace Shader{

class DepthRenderer : public OffScreenRendererBase
{
public:
	DepthRenderer(const int width, const int height, const float& size);

	~DepthRenderer(void);

	void setVisualParticles(const VisualParticleList& visualParticles);

protected:
	virtual void onRender();

	virtual void onInit();

	virtual void onIdle(){};

private:
	std::vector<double> positions;
	std::vector<double> densities;

	const float& size;
};

	}
}
#endif