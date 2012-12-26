#ifndef __SCREEN_SPACE_FLUID_RENDERER_H__
#define __SCREEN_SPACE_FLUID_RENDERER_H__

#include "OffScreenRendererBase.h"

namespace Amorphous{
	namespace Shader{
		class OffScreenRenderer;
		class RenderBufferObject;

class ScreenSpaceFluidRenderer : public OffScreenRendererBase
{
public:
	ScreenSpaceFluidRenderer(const int width, const int height);

	virtual ~ScreenSpaceFluidRenderer();

	void setOffScreenRenderer(OffScreenRendererBase* offScreenRenderer) { this->offScreenRenderer = offScreenRenderer; }

	virtual void renderOffScreen();

protected:
	virtual void onRender();

	virtual void onInit();

	virtual void onIdle(){};
	
	Amorphous::Shader::OffScreenRendererBase* offScreenRenderer;
	Amorphous::Shader::FrameBufferObject* frameBufferObject;
};

	}
}

#endif