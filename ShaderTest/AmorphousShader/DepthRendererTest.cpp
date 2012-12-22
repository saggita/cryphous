#include "../AmorphousGeom/AmorphousGeom.h"
#include "../AmorphousShader/AmorphousShader.h"
#include "../AmorphousShader/DepthRenderer.h"
#include "DepthRendererTest.h"

using namespace Amorphous::Geom;
using namespace Amorphous::Shader;

const float size = 50.0f;

DepthRendererTest::DepthRendererTest(const int width, const int height, DepthRenderer* depthRenderer) :
OnScreenRendererBase( width, height)
{
	offScreenRenderer = depthRenderer;
}