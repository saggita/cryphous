#pragma once

#include <vector>
#include <memory>

#include "../AmorphousShader/ShaderParticle.h"

class PointRendererTest : public Crystal::Shader::OnScreenRendererBase
{
public:
	PointRendererTest(const int width, const int height, std::vector<Crystal::Shader::PolygonModel>& solidModels);

	~PointRendererTest(void);

protected:
	virtual void onRender();

	virtual void onIdle();

	virtual void onInit();

private:
	Crystal::Shader::PBFR renderer;
	Crystal::Shader::PBFRSetting setting;
	Crystal::Shader::VisualParticleList visualParticles;
	std::vector<Crystal::Shader::PolygonModel>& solidModels;
};
