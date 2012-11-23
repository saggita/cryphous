#include "StdAfx.h"

#include "BackGroundRenderer.h"
#include "PBFRSetting.h"

#include <cassert>
#include <boost/foreach.hpp>

using namespace Amorphous::Geom;
using namespace Amorphous::Color;
using namespace Amorphous::Shader;

BackGroundRenderer::BackGroundRenderer(const int width, const int height, const float& intensity) :
OffScreenRendererBase( width, height),
intensity( intensity),
solidModels(0)
{
}

BackGroundRenderer::~BackGroundRenderer(void)
{
}

void BackGroundRenderer::setBackGround(TextureObject* texture)
{
	textureObject.reset( texture);
}

void BackGroundRenderer::onInit()
{	
	//projectionMatrix.setPerspectiveMatrix(0.0f, 1.0f, 0.0f, 1.0f, 0.01f, 100.0f );
	projectionMatrix.setPerspectiveMatrix(-0.5f, 0.5f, 0.0f, 1.0f, 0.01f, 100.0f );
	shaderObject.createShader("BackGround");

	std::vector<GLfloat> pixels(64 * 64 * 4, 1.0f);
	setBackGround( new TextureObject( pixels, 64, 64 ) );

	const std::string polygonFileName = "../PolygonModels/ground.obj";
	polygonModel.readFromObjFile(polygonFileName);
}

void BackGroundRenderer::onRender()
{
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glEnable(GL_DEPTH_TEST);

	textureObject->apply(0);
	shaderObject.apply();

	shaderObject.setUniformMatrix("projectionMatrix", projectionMatrix);
	shaderObject.setUniformMatrix("modelviewMatrix", getModelviewMatrix());
	shaderObject.setUniformTexture("textureObject", *textureObject);
	
	drawBackGround();
	drawSolid();
	
	shaderObject.release();
	textureObject->release();

	glDisable( GL_DEPTH_TEST );
	glFlush();
}

void BackGroundRenderer::drawBackGround()
{
	std::vector<double>& points = polygonModel.getVertices();
	shaderObject.setVertex("position", points);
	std::vector<double>& texCoord = polygonModel.getTextureCoordinates();
	shaderObject.setVertexAttrib("texCoord", texCoord, 2);
	shaderObject.setUniform("intensity", intensity );
	shaderObject.setUniform("useTexture", 1);
	shaderObject.drawTriangles( points.size() / 3 );
}

void BackGroundRenderer::drawSolid()
{
	if( solidModels == 0 ) {
		return;
	}
	BOOST_FOREACH( const PolygonModel& solidModel, *solidModels ) {
		std::vector<double>& points = solidModel.getVertices();
		shaderObject.setVertex("position", points);
		std::vector<double>& texCoord = solidModel.getTextureCoordinates();
		shaderObject.setVertexAttrib("texCoord", texCoord, 2);
		shaderObject.setUniform("intensity", 1.0f );
		shaderObject.setUniform("useTexture", 0);
		shaderObject.drawTriangles( points.size() / 3 );
	}
}