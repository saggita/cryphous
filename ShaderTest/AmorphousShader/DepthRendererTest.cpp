#include "../AmorphousGeom/AmorphousGeom.h"
#include "../AmorphousShader/AmorphousShader.h"
#include "../AmorphousShader/DepthRenderer.h"
#include "DepthRendererTest.h"

using namespace Amorphous::Geom;
using namespace Amorphous::Color;
using namespace Amorphous::Shader;

const float size = 50.0f;

DepthRendererTest::DepthRendererTest(const int width, const int height) :
OnScreenRendererBase( width, height)
{
	DepthRenderer* depthRenderer = new DepthRenderer( getWidth(), getHeight(), size);
	VisualParticleList visualParticles;
	visualParticles.push_back( VisualParticle() );
	visualParticles.push_back( VisualParticle( Vector3d<>( 0.1, 0.0, -5 ), 1.0 ) );
	depthRenderer->setVisualParticles( visualParticles );
	offScreenRenderer = depthRenderer;
}