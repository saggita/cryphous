#ifndef __SCREEN_SPACE_FLUID_RENDERER_H__
#define __SCREEN_SPACE_FLUID_RENDERER_H__

#include "OffScreenRendererBase.h"

namespace Crystal{
	namespace Shader{
		class OffScreenRenderer;
		class RenderBufferObject;

class ScreenSpaceFluidRenderer : public OffScreenRendererBase
{
public:
	ScreenSpaceFluidRenderer(const int width, const int height);

	virtual ~ScreenSpaceFluidRenderer();

protected:
	virtual void onRender();

	virtual void onInit();

	virtual void onIdle(){};
	
};

	}
}

#endif