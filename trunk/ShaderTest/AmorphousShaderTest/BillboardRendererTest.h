#pragma once

#include <vector>
#include <memory>

//#include "../AmorphousShader/ShaderParticle.h"

class BillboardRendererTest : public Amorphous::Shader::OnScreenRendererBase
{
public:
	BillboardRendererTest(const int width, const int height, const std::vector<Amorphous::Shader::PolygonModel>& solidModels);

	~BillboardRendererTest(void);

protected:
	virtual void onRender();

	virtual void onIdle();

	virtual void onInit();

private:
	Amorphous::Shader::FlameRenderer renderer;
	Amorphous::Shader::PBFRSetting setting;
	std::vector<Amorphous::Shader::PolygonModel> solidModels;
	Amorphous::Color::VisualParticleList visualParticles;
};
