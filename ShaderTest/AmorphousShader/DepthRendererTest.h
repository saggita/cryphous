#pragma once

#include <memory>

namespace Amorphous{
	namespace Shader{
		class DepthRenderer;
	}
}

class DepthRendererTest : public Amorphous::Shader::OnScreenRendererBase
{
public:
	DepthRendererTest(const int width, const int height);

protected:

	virtual void onRender();

	virtual void onIdle(){};

	virtual void onInit();

private:
	void drawPolygon();

	std::auto_ptr<Amorphous::Shader::FrameBufferObject> frameBufferObject;
};