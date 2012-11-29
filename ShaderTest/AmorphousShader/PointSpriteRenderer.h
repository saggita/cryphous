#ifndef __POINT_SPRITE_RENDERER_H__
#define __POINT_SPRITE_RENDERER_H__

#include "OffScreenRendererBase.h"
#include "VisualParticle.h"
#include <memory>

namespace Amorphous{
	namespace Shader{

class PointSpriteRenderer : public OffScreenRendererBase
{
public:
	PointSpriteRenderer(const int width, const int height, const float& size, const float& alpha);

	~PointSpriteRenderer(void);

	void setVisualParticles(const Amorphous::Color::VisualParticleList& visualParticles);

protected:
	virtual void onRender();

	virtual void onInit();

	virtual void onIdle(){};

private:
	std::vector<double> positions;
	std::vector<double> colors;

	const float& size;
	const float& alpha;
	
	void initColorTransferTexture();
};

	}
}
#endif