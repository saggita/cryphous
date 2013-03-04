#ifndef __SPLASH_RENDERER_H__
#define __SPLASH_RENDERER_H__

#include "OffScreenRendererBase.h"
#include "VisualParticle.h"

namespace Cryphous{
	namespace Shader{

class SplashRenderer : public OffScreenRendererBase
{
public:
	SplashRenderer(const int width, const int height, float& size, float& alpha);

	~SplashRenderer(void);

	void setVisualParticles(const VisualParticleList& visualParticles);

protected:
	virtual void onRender();

	virtual void onInit();

	virtual void onIdle(){};

private:
	std::vector<double> positions;
	std::vector<double> colors;

	float& size;
	float& alpha;
};

	}
}
#endif