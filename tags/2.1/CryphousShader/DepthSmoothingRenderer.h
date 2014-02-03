#ifndef __CRYPHOUS_DEPTH_SMOOTHING_RENDERER_H__
#define __CRYPHOUS_DEPTH_SMOOTHING_RENDERER_H__

#include "OffScreenRendererBase.h"

namespace Cryphous{
	namespace Shader{
		
class DepthSmoothingRenderer : public OffScreenRendererBase
{
public:
	DepthSmoothingRenderer(const int width, const int height);

	virtual ~DepthSmoothingRenderer();

	void setDepthTexture(TextureObject* depthTexture) { this->depthTexture = depthTexture; }

protected:
	virtual void onRender();

	virtual void onInit();

	virtual void onIdle(){};

	TextureObject* depthTexture;
};

	}
}

#endif