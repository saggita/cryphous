#pragma once

#include <memory>

namespace Amorphous{
	namespace Shader{
		class PointSpriteRenderer;
	}
}

class PointSpriteRendererTest : public Amorphous::Shader::OnScreenRendererBase
{
public:
	PointSpriteRendererTest(const int width, const int height);

protected:

	virtual void onRender();

	virtual void onIdle(){};

	virtual void onInit();

	std::auto_ptr<Amorphous::Shader::FrameBufferObject> frameBufferObject;
};