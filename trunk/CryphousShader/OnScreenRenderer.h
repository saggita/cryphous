#ifndef __CRYPHOUS_ON_SCREEN_RENDERER_BASE_H__
#define __CRYPHOUS_ON_SCREEN_RENDERER_BASE_H__

#include "ScreenRendererBase.h"

namespace Cryphous{
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

	void setTexture(TextureObject* texture) { this->texture = texture; }

private:
	virtual void onIdle(){};

	virtual void onInit();

	virtual void onRender();
	
	Cryphous::Shader::TextureObject* texture;
};

	}
}

#endif