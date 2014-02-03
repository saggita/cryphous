#ifndef __ON_SCREEN_RENDERER_BASE_H__
#define __ON_SCREEN_RENDERER_BASE_H__

#include "ScreenRendererBase.h"

namespace Crystal{
	namespace Shader{
		class OffScreenRendererBase;
		class FrameBufferObject;
		class RenderingCommandStack;
		class ShaderCommandStack;

class OnScreenRenderer : public ScreenRendererBase
{
public:
	OnScreenRenderer();

	virtual ~OnScreenRenderer();

	void render();

	void idle();

	void setTexture(TextureObject* texture) { this->texture = texture; }

private:
	virtual void onIdle(){};

	virtual void onInit();

	virtual void onRender();

	void onRender(RenderingCommandStack& commands, ShaderCommandStack& sCommands);
	
	Crystal::Shader::TextureObject* texture;
};

	}
}

#endif