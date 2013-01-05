#ifndef __DEPTH_SMOOTHING_RENDERER_H__
#define __DEPTH_SMOOTHING_RENDERER_H__

#include "OffScreenRendererBase.h"

namespace Crystal{
	namespace Shader{
		
class DepthSmoothingRenderer : public OffScreenRendererBase
{
public:
	DepthSmoothingRenderer(const int width, const int height);

	virtual ~DepthSmoothingRenderer();

protected:
	virtual void onRender();

	virtual void onInit();

	virtual void onIdle(){};
};

	}
}

#endif