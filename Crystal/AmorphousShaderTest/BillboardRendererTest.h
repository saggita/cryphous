#pragma once

#include <vector>
#include <memory>

#include "../AmorphousShader/ShaderParticle.h"

class BillboardRendererTest : public Crystal::Shader::OnScreenRendererBase
{
public:
	BillboardRendererTest(const int width, const int height, const std::vector<Crystal::Shader::PolygonModel>& solidModels);

	~BillboardRendererTest(void);

protected:
	virtual void onRender();

	virtual void onIdle();

	virtual void onInit();

private:
	Crystal::Shader::FluidRenderer renderer;
	Crystal::Shader::PBFRSetting setting;
	std::vector<Crystal::Shader::PolygonModel> solidModels;
	Crystal::Shader::VisualParticleVector visualParticles;
};
