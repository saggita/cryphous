#include "Renderer.h"

#include "../CrystalPhysics/Uncopyable.h"
#include "../CrystalPhysics/Particle.h"
#include "../CrystalPhysics/SimulationSetting.h"
#include "../CrystalPhysics/PhysicsObjectFactory.h"
#include "../CrystalPhysics/PhysicsObject.h"
#include "../CrystalPhysics/Profiler.h"

#include "DepthRenderer.h"
#include "DepthSmoothingRenderer.h"
#include "ScreenSpaceFluidRenderer.h"
#include "OnScreenRenderer.h"

#include <cassert>
#include <cmath>
#include <cstdlib>

using namespace Crystal::Shader;
using namespace Crystal::Physics;
using namespace Crystal::Geom;

void Renderer::rendering(PhysicsObjectFactory *factory, const int width, const int height, const Box& boundaryBox)
{	
	Physics::Profiler::get()->start("Rendering->");

	openGLWrapper.BeginRendering();

	const float size = 10;

	DepthRenderer depth(width, height, size);

	DepthSmoothingRenderer smoothing(width, height);
	smoothing.setOffScreenRenderer( &depth);

	ScreenSpaceFluidRenderer ssfr(width, height);
	ssfr.setOffScreenRenderer( &smoothing);
	
	OnScreenRenderer onscreen(width, height);
	onscreen.setOffScreenRenderer( &ssfr );
	onscreen.render();

	//glFlush();
	openGLWrapper.EndRendering();

	Physics::Profiler::get()->end("Rendering->");
}