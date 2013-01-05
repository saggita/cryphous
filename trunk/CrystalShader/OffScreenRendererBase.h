#ifndef __OFF_SCREEN_RENDERER_BASE_H__
#define __OFF_SCREEN_RENDERER_BASE_H__

#include "ScreenRendererBase.h"

namespace Amorphous{
	namespace Shader{

class FrameBufferObject;

class OffScreenRendererBase : public ScreenRendererBase
{
public:
	OffScreenRendererBase(const int width, const int height);

	virtual ~OffScreenRendererBase(void);

	void render(const FrameBufferObject& frameBufferObject);

	void setOffScreenRenderer(OffScreenRendererBase* offScreenRenderer) { this->offScreenRenderer = offScreenRenderer; }

protected:
	virtual void onRender() = 0;

	virtual void onInit() = 0;

	virtual void onIdle(){};
	
	Amorphous::Shader::OffScreenRendererBase* offScreenRenderer;
	Amorphous::Shader::FrameBufferObject* frameBufferObject;

private:
	void renderOffScreen();
};

	}
}

#endif