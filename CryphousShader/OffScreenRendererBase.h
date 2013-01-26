#ifndef __OFF_SCREEN_RENDERER_BASE_H__
#define __OFF_SCREEN_RENDERER_BASE_H__

#include "ScreenRendererBase.h"

namespace Cryphous{
	namespace Shader{

class FrameBufferObject;

class OffScreenRendererBase : public ScreenRendererBase
{
public:
	OffScreenRendererBase(const int width, const int height);

	virtual ~OffScreenRendererBase(void);

	void render();

	FrameBufferObject* getFrameBufferObject() { return frameBufferObject; }

protected:
	virtual void onRender() = 0;

	virtual void onInit() = 0;

	virtual void onIdle(){};

	FrameBufferObject* frameBufferObject;
};

	}
}

#endif