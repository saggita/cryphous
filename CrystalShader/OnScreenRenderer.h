#ifndef __ON_SCREEN_RENDERER_BASE_H__
#define __ON_SCREEN_RENDERER_BASE_H__

#include "ScreenRendererBase.h"

namespace Crystal{
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

	void setPointSpriteTextureObject(TextureObject* psTexture) { this->psTexture = psTexture; }

private:
	virtual void onIdle(){};

	virtual void onInit();

	virtual void onRender();
	
	Crystal::Shader::TextureObject* psTexture;
};

	}
}

#endif