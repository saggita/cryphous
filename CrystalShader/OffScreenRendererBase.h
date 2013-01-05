#ifndef __OFF_SCREEN_RENDERER_BASE_H__
#define __OFF_SCREEN_RENDERER_BASE_H__

#include "ScreenRendererBase.h"

namespace Crystal{
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
	
	Crystal::Shader::OffScreenRendererBase* offScreenRenderer;
	Crystal::Shader::FrameBufferObject* frameBufferObject;

private:
	void renderOffScreen();
};

	}
}

#endif