#pragma once

#include <vector>
#include <memory>

#include "../CrystalPhysics/PhysicsObjectFactory.h"
#include "../CrystalPhysics/Simulation.h"

class PointRendererTest : public Crystal::Shader::OnScreenRendererBase
{
public:
	PointRendererTest(const int width, const int height);

	~PointRendererTest(void);

protected:
	virtual void onRender();

	virtual void onIdle();

	virtual void onInit();

private:
	Crystal::Shader::PBFR renderer;
	Crystal::Shader::PBFRSetting setting;
	Crystal::Shader::VisualParticleVector visualParticles;
	Crystal::Physics::PhysicsObjectFactory factory;
	Crystal::Physics::Simulation simulation;
	Crystal::Physics::SimulationSetting ssetting;
};
