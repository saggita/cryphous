#ifndef __CRYPHOUS_THICKNESS_RENDERER_H__
#define __CRYPHOUS_THICKNESS_RENDERER_H__

#include "OffScreenRendererBase.h"
#include "VisualParticle.h"
#include <memory>

namespace Cryphous{
	namespace Shader{

class ThicknessRenderer : public OffScreenRendererBase
{
public:
	ThicknessRenderer(const int width, const int height, float& size, float& alpha);

	~ThicknessRenderer(void);

	void setVisualParticles(VisualParticleCollection* visualParticles) { this->collection = visualParticles; }

protected:
	virtual void onRender();

	virtual void onInit();

	virtual void onIdle(){};

private:
	VisualParticleCollection* collection;

	float& size;
	float& alpha;
};

	}
}
#endif