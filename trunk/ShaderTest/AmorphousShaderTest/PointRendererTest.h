#pragma once

#include <vector>
#include <memory>

//#include "../AmorphousShader/ShaderParticle.h"

class PointRendererTest : public Amorphous::Shader::OnScreenRendererBase
{
public:
	PointRendererTest(const int width, const int height, std::vector<Amorphous::Shader::PolygonModel>& solidModels);

	~PointRendererTest(void);

protected:
	virtual void onRender();

	virtual void onIdle();

	virtual void onInit();

private:
	Amorphous::Shader::PBFR renderer;
	Amorphous::Shader::PBFRSetting setting;
	Amorphous::Color::VisualParticleList visualParticles;
	std::vector<Amorphous::Shader::PolygonModel>& solidModels;
};
