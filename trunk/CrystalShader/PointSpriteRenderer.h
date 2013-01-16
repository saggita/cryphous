#ifndef __POINT_SPRITE_RENDERER_H__
#define __POINT_SPRITE_RENDERER_H__

#include "OffScreenRendererBase.h"
#include "VisualParticle.h"
#include <memory>

namespace Crystal{
	namespace Shader{

class PointSpriteRenderer : public OffScreenRendererBase
{
public:
	PointSpriteRenderer(const int width, const int height, float& size, float& alpha);

	~PointSpriteRenderer(void);

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
	
	void initColorTransferTexture();
};

	}
}
#endif