#ifndef __CRYPHOUS_SCREEN_SPACE_FLUID_RENDERER_H__
#define __CRYPHOUS_SCREEN_SPACE_FLUID_RENDERER_H__

#include "OffScreenRendererBase.h"

namespace Cryphous{
	namespace Shader{
		class OffScreenRenderer;
		class RenderBufferObject;

class ScreenSpaceFluidRenderer : public OffScreenRendererBase
{
public:
	ScreenSpaceFluidRenderer(const int width, const int height);

	virtual ~ScreenSpaceFluidRenderer();

	void setDepthSmoothingTexture(TextureObject* depthSmoothingTexture) { this->depthSmoothingTexture = depthSmoothingTexture; }

	void setThicknessTexture(TextureObject* thicknessTexture) { this->thicknessTexture = thicknessTexture; }

	void setBackgroundTexture(TextureObject* backgroundTexture) { this->backgroundTexture = backgroundTexture; }

protected:
	virtual void onRender();

	virtual void onInit();

	virtual void onIdle(){};
	
	TextureObject* depthSmoothingTexture;
	TextureObject* thicknessTexture;
	TextureObject* backgroundTexture;
};

	}
}

#endif