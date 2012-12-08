#pragma once

#include <memory>

namespace Amorphous{
	namespace Shader{
		class BackGroundRenderer;
	}
}

class BackGroundRendererTest : public Amorphous::Shader::OnScreenRendererBase
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

	std::auto_ptr<Amorphous::Shader::FrameBufferObject> frameBufferObject;
	Amorphous::Shader::BackGroundRenderer* backGroundRenderer;
	float intensity;
};