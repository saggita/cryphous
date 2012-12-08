#pragma once

#include <memory>

namespace Amorphous{
	namespace Shader{
		class BillboardRenderer;
	}
}

class BillboardRendererTest : public Amorphous::Shader::OnScreenRendererBase
{
public:
	BillboardRendererTest(const int width, const int height);

	~BillboardRendererTest(void);

protected:

	virtual void onRender();

	virtual void onIdle(){};

	virtual void onInit();

private:
	void drawPolygon();

	std::auto_ptr<Amorphous::Shader::FrameBufferObject> frameBufferObject;
	Amorphous::Shader::BillboardRenderer* billboardRenderer;
	Amorphous::Color::VisualParticleList visualParticles;
};