#ifndef __ON_SCREEN_RENDERER_BASE_H__
#define __ON_SCREEN_RENDERER_BASE_H__

#include "ScreenRendererBase.h"

namespace Amorphous{
	namespace Shader{
		class OffScreenRendererBase;
		class FrameBufferObject;

class OnScreenRenderer : public ScreenRendererBase
{
public:
	OnScreenRenderer(const int width, const int height);

	virtual ~OnScreenRenderer();

	void render();

	void idle();

	void setOffScreenRenderer(Amorphous::Shader::OffScreenRendererBase* offScreenRenderer) { this->offScreenRenderer = offScreenRenderer; }

private:
	virtual void onIdle(){};

	virtual void onInit();

	virtual void onRender();
	
	Amorphous::Shader::OffScreenRendererBase* offScreenRenderer;
	Amorphous::Shader::FrameBufferObject* frameBufferObject;
};

	}
}

#endif