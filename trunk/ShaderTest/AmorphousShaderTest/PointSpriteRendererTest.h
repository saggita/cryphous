#pragma once

#include <vector>
#include <memory>

#include "../AmorphousShader/ShaderParticle.h"

class PointSpriteRendererTest : public Amorphous::Shader::OnScreenRendererBase
{
public:
	PointSpriteRendererTest(const int width, const int height, const std::vector<Amorphous::Shader::PolygonModel>& solidModels);

	~PointSpriteRendererTest(void);

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
