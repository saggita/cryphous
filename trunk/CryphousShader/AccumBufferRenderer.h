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

	void setTextures(TextureObject* texture1, TextureObject* texture2) { this->texture1 = texture1; this->texture2 = texture2; }

protected:
	virtual void onRender();

	virtual void onInit();

	virtual void onIdle(){};

	TextureObject* texture1;
	TextureObject* texture2;
};

	}
}

#endif