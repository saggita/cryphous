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

	~PointSpriteRendererTest(void);

protected:

	virtual void onRender();

	virtual void onIdle(){};

	virtual void onInit();

private:
	void drawPolygon();

	std::auto_ptr<Amorphous::Shader::FrameBufferObject> frameBufferObject;
};