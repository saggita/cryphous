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
#include "PointSpriteRenderer.h"
#include "Camera.h"

#include <cassert>
#include <cmath>
#include <cstdlib>

using namespace Crystal::Shader;
using namespace Crystal::Physics;
using namespace Crystal::Geom;

void Renderer::init()
{
	openGLWrapper.SetCurrentRenderingContext();

}

void Renderer::rendering(PhysicsObjectFactory *factory, const int width, const int height, const Box& boundaryBox)
{	
	Physics::Profiler::get()->start("Rendering->");

	openGLWrapper.BeginRendering();

	//Camera::get()->zoom = -0.1f;

	pointSpriteRenderer = new PointSpriteRenderer( 512, 512, 50, 1 );
	onScreenRenderer = new OnScreenRenderer( 512, 512 );
	depthRenderer = new DepthRenderer( 512, 512, 50 );
	depthSmoothingRenderer = new DepthSmoothingRenderer( 512, 512 );
	screenSpaceFluidRenderer = new ScreenSpaceFluidRenderer( 512, 512 );

	VisualParticleList visualParticles;
	visualParticles.push_back( VisualParticle() );
	visualParticles.push_back( VisualParticle( Crystal::Geom::Vector3d( 0.1f, 0.0f, -5.0f ), 1.0 ) );

	for( size_t i = 0; i < 10; ++i ) {
		visualParticles.push_back( VisualParticle( Crystal::Geom::Vector3d( 0.01f * i, 0.0f, -1.0f ), 1.0 ) );
	}

	pointSpriteRenderer->setVisualParticles( visualParticles );
	depthRenderer->setVisualParticles( visualParticles );

	depthSmoothingRenderer->setOffScreenRenderer( depthRenderer );
	screenSpaceFluidRenderer->setOffScreenRenderer( depthSmoothingRenderer );
	onScreenRenderer->setOffScreenRenderer( screenSpaceFluidRenderer );
	
	onScreenRenderer->init();
	onScreenRenderer->render();

	glFlush();
	openGLWrapper.EndRendering();

	Physics::Profiler::get()->end("Rendering->");
}