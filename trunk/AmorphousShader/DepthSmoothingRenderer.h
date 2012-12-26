#ifndef __DEPTH_SMOOTHING_RENDERER_H__
#define __DEPTH_SMOOTHING_RENDERER_H__

#include "OffScreenRendererBase.h"

namespace Amorphous{
	namespace Shader{
		class OffScreenRenderer;
		class RenderBufferObject;

class DepthSmoothingRenderer : public OffScreenRendererBase
{
public:
	DepthSmoothingRenderer(const int width, const int height);

	virtual ~DepthSmoothingRenderer();

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