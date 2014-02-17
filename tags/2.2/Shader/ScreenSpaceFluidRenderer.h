#ifndef __SCREEN_SPACE_FLUID_RENDERER_H__
#define __SCREEN_SPACE_FLUID_RENDERER_H__

#include "OffScreenRendererBase.h"

namespace Crystal{
	namespace Shader{
		class OffScreenRenderer;
		class RenderBufferObject;
		class RenderingCommandStack;
		class ShaderCommandStack;

class ScreenSpaceFluidRenderer : public OffScreenRendererBase
{
public:
	ScreenSpaceFluidRenderer();

	virtual ~ScreenSpaceFluidRenderer();

	void setDepthSmoothingTexture(TextureObject* depthSmoothingTexture) { this->depthSmoothingTexture = depthSmoothingTexture; }

	void setThicknessTexture(TextureObject* thicknessTexture) { this->thicknessTexture = thicknessTexture; }

	void setBackgroundTexture(TextureObject* backgroundTexture) { this->backgroundTexture = backgroundTexture; }

protected:
	virtual void onRender();

	void onRender(RenderingCommandStack& commands, ShaderCommandStack& sCommands);

	virtual void onInit();

	virtual void onIdle(){};
	
	TextureObject* depthSmoothingTexture;
	TextureObject* thicknessTexture;
	TextureObject* backgroundTexture;
};

	}
}

#endif