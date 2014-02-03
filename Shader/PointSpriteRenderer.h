#ifndef __CRYSTAL_GRAPHICS_POINT_SPRITE_RENDERER_H__
#define __CRYSTAL_GRAPHICS_POINT_SPRITE_RENDERER_H__

#include "OffScreenRendererBase.h"
#include "VisualParticle.h"

namespace Crystal{
	namespace Shader{
		class RenderingCommandStack;
		class ShaderCommandStack;

class PointSpriteRenderer : public OffScreenRendererBase
{
public:
	PointSpriteRenderer(float& size, float& alpha);

	~PointSpriteRenderer(void);

	void setVisualParticles(const std::vector<float>& positions, const std::vector<float>& colors) {
		this->positions = positions;
		this->colors = colors;
	}

protected:
	virtual void onRender();

	void onRender(RenderingCommandStack& commands, ShaderCommandStack& sCommands);

	virtual void onInit();

	virtual void onIdle(){};

private:
	std::vector<float> positions;
	std::vector<float> colors;

	float& size;
	float& alpha;
	
	void initColorTransferTexture();
};

	}
}
#endif