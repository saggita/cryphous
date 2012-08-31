#pragma once

#include "../CrystalPhysics/Simulation.h"

class BillboardRendererTest : public Crystal::Shader::OnScreenRendererBase
{
public:
	BillboardRendererTest(const int width, const int height);

	~BillboardRendererTest(void);

protected:
	virtual void onRender();

	virtual void onIdle();

	virtual void onInit();

private:
	Crystal::Shader::FluidRenderer renderer;
	Crystal::Shader::PBFRSetting setting;
	Crystal::Shader::VisualParticleVector visualParticles;

	Crystal::Physics::PhysicsObjectFactory factory;
	Crystal::Physics::Simulation simulation;
	Crystal::Physics::SimulationSetting ssetting;
};
