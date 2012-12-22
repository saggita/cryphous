#ifndef __ON_SCREEN_RENDERER_BASE_H__
#define __ON_SCREEN_RENDERER_BASE_H__

#include "ScreenRendererBase.h"

namespace Amorphous{
	namespace Shader{
		class OffScreenRendererBase;
		class FrameBufferObject;

class OnScreenRendererBase : public ScreenRendererBase
{
public:
	OnScreenRendererBase(const int width, const int height);

	virtual ~OnScreenRendererBase();

	void render();

	void idle();

protected:
	virtual void onIdle(){};

	virtual void onInit();

	virtual void onRender();
	
	Amorphous::Shader::OffScreenRendererBase* offScreenRenderer;
	Amorphous::Shader::FrameBufferObject* frameBufferObject;
};

	}
}

#endif