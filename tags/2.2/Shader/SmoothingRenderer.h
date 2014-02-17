#ifndef __CRYSTAL_GRAPHICS_SMOOTHING_RENDERER_H__
#define __CRYSTAL_GRAPHICS_SMOOTHING_RENDERER_H__

#include "OffScreenRendererBase.h"

namespace Crystal{
	namespace Shader{
		class RenderingCommandStack;
		class ShaderCommandStack;
		
class SmoothingRenderer : public OffScreenRendererBase
{
public:
	SmoothingRenderer();

	virtual ~SmoothingRenderer();

	void setDepthTexture(TextureObject* depthTexture) { this->depthTexture = depthTexture; }

protected:
	virtual void onRender();

	void onRender(ShaderCommandStack& sCommand);

	virtual void onInit();

	virtual void onIdle(){};

	TextureObject* depthTexture;
};

	}
}

#endif