#pragma once

#include <memory>

namespace Amorphous{
	namespace Shader{
		class PolygonRenderer;
	}
}

class DepthRendererTest : public Amorphous::Shader::OnScreenRendererBase
{
public:
	DepthRendererTest(const int width, const int height);

	~DepthRendererTest(void);

protected:

	virtual void onRender();

	virtual void onIdle(){};

	virtual void onInit();

private:
	void drawPolygon();

	std::auto_ptr<Amorphous::Shader::FrameBufferObject> frameBufferObject;
	Amorphous::Shader::PBFRSetting setting;
	Amorphous::Shader::PolygonRenderer* polygonRenderer;
};