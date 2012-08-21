#pragma once

#include <memory>

namespace Crystal{
	namespace Shader{
		class PolygonRenderer;
	}
}

class PolygonRendererTest : public Crystal::Shader::OnScreenRendererBase
{
public:
	PolygonRendererTest(const int width, const int height);

	~PolygonRendererTest(void);

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