#ifndef __ACCUM_BUFFER_RENDERER_H__
#define __ACCUM_BUFFER_RENDERER_H__

#include "OffScreenRendererBase.h"

namespace Cryphous{
	namespace Shader{
		
class AccumBufferRenderer : public OffScreenRendererBase
{
public:
	AccumBufferRenderer(const int width, const int height);

	virtual ~AccumBufferRenderer();

	void setTexture(TextureObject* texture) { this->texture = texture; }

protected:
	virtual void onRender();

	virtual void onInit();

	virtual void onIdle(){};

	TextureObject* texture;
};

	}
}

#endif