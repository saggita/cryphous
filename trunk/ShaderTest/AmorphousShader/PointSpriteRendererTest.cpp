#include "../AmorphousGeom/AmorphousGeom.h"
#include "../AmorphousShader/AmorphousShader.h"
#include "../AmorphousShader/PointSpriteRenderer.h"
#include "PointSpriteRendererTest.h"

using namespace Amorphous::Geom;
using namespace Amorphous::Color;
using namespace Amorphous::Shader;

const float size = 50.0f;
const float alpha = 1.0f;

PointSpriteRendererTest::PointSpriteRendererTest(const int width, const int height) :
OnScreenRendererBase( width, height)
{
	PointSpriteRenderer* pointSpriteRenderer = new PointSpriteRenderer( getWidth(), getHeight(), size, alpha);
	VisualParticleList visualParticles;
	visualParticles.push_back( VisualParticle() );
	pointSpriteRenderer->setVisualParticles( visualParticles );
	offScreenRenderer = pointSpriteRenderer;
}