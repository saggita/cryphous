#pragma once

#include <memory>

namespace Amorphous{
	namespace Shader{
		class PolygonRenderer;
	}
}

class PolygonRendererTest : public Amorphous::Shader::OnScreenRendererBase
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

	std::auto_ptr<Amorphous::Shader::FrameBufferObject> frameBufferObject;
	Amorphous::Shader::PolygonRenderer* polygonRenderer;
};