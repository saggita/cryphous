#ifndef __ON_SCREEN_RENDERER_BASE_H__
#define __ON_SCREEN_RENDERER_BASE_H__

#include "ScreenRendererBase.h"

namespace Crystal{
	namespace Shader{

class OnScreenRendererBase : public ScreenRendererBase
{
public:
	OnScreenRendererBase(const int width, const int height);

	~OnScreenRendererBase(){};

	void render();

	void idle();

protected:
	virtual void onIdle() = 0;
};

	}
}

#endif