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

	~OffScreenRendererBase(void);

	void render(const FrameBufferObject& frameBufferObject);	
};

	}
}

#endif