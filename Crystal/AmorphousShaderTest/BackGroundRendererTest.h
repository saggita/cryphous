#pragma once

#include <memory>

namespace Crystal{
	namespace Shader{
		class BackGroundRenderer;
	}
}

class BackGroundRendererTest : public Crystal::Shader::OnScreenRendererBase
{
public:
	BackGroundRendererTest(const int width, const int height);

	~BackGroundRendererTest(void);

protected:

	virtual void onRender();

	virtual void onIdle(){};

	virtual void onInit();

private:
	void drawPolygon();

	std::auto_ptr<Crystal::Shader::FrameBufferObject> frameBufferObject;
	Crystal::Shader::BackGroundRenderer* backGroundRenderer;
	float intensity;
};