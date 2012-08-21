#pragma once

#include <memory>

namespace Crystal{
	namespace Shader{
		class PolygonRenderer;
	}
}

class DepthRendererTest : public Crystal::Shader::OnScreenRendererBase
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

	std::auto_ptr<Crystal::Shader::FrameBufferObject> frameBufferObject;
	Crystal::Shader::PBFRSetting setting;
	Crystal::Shader::PolygonRenderer* polygonRenderer;
};