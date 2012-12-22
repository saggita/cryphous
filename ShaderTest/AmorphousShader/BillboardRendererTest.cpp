#include "../AmorphousGeom/AmorphousGeom.h"
#include "../AmorphousShader/AmorphousShader.h"
#include "BillboardRendererTest.h"

using namespace Amorphous::Geom;
using namespace Amorphous::Color;
using namespace Amorphous::Shader;

const float size = 10.0f;
const float alpha = 1.0f;

BillboardRendererTest::BillboardRendererTest(const int width, const int height) :
OnScreenRendererBase( width, height)
{
	BillboardRenderer* billboardRenderer = new BillboardRenderer( getWidth(), getHeight(), size, alpha);
	VisualParticleList visualParticles;
	visualParticles.push_back( VisualParticle() );
	billboardRenderer->setVisualParticles( visualParticles );
	offScreenRenderer = billboardRenderer;
}

BillboardRendererTest::~BillboardRendererTest(void)
{
	delete offScreenRenderer;
}

void BillboardRendererTest::onRender()
{
	offScreenRenderer->render( *frameBufferObject );

	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glEnable( GL_DEPTH_TEST );

	TextureObject& textureObject = frameBufferObject->getTextureObject();
	textureObject.apply( 0 );

	GLfloat colorOffset[3] = {0.0f, 0.0f, 0.0f};

	std::vector<double> points(12);
	points[0] = 0.0; points[1] = 1.0; points[2] = 0.0;
	points[3] = 0.0; points[4] = 0.0; points[5] = 0.0;
	points[6] = 1.0; points[7] = 0.0; points[8] = 0.0;
	points[9] = 1.0; points[10] = 1.0; points[11] = 0.0;
	
	shaderObject.apply();
	shaderObject.setUniformMatrix("projectionMatrix", projectionMatrix);
	shaderObject.setUniformMatrix("modelviewMatrix", GLSLMatrix());
	shaderObject.setUniformTexture("offScreenTexture", textureObject);
	shaderObject.setVertex("position", points );
	shaderObject.drawQuads( 4);
	shaderObject.release();

	textureObject.release();

	glDisable( GL_DEPTH_TEST );
}

void BillboardRendererTest::onInit()
{
	frameBufferObject.reset( new FrameBufferObject(getWidth(), getHeight(), false) );

	offScreenRenderer->init();

	shaderObject.createShader("Quad");

	projectionMatrix.setOrthogonalMatrix( 0.0, 1.0, 0.0, 1.0, -1.0, 1.0 );
}