#include "StdAfx.h"

#include "PolygonRenderer.h"

#include "ShaderObject.h"
#include "PolygonModel.h"

#include <cassert>

using namespace Amorphous::Geom;
using namespace Amorphous::Color;
using namespace Amorphous::Shader;

PolygonRenderer::PolygonRenderer(const int width, const int height, const std::string& polygonFileName,const PBFRSetting& setting) :
OffScreenRendererBase( width, height),
polygonFileName( polygonFileName),
setting( setting)
{
}

PolygonRenderer::~PolygonRenderer(void)
{
}

void PolygonRenderer::onInit()
{	
	projectionMatrix.setPerspectiveMatrix(0.0f, 1.0f, 0.0f, 1.0f, 0.01f, 100.0f );
	shaderObject.createShader("lighting");
	polygonModel.readFromObjFile(polygonFileName);
	TextureCreator creator;
	creator.createTexture(64);
	textureObject.reset( new TextureObject( 64, 64 ));
	textureObject->initAlphaTexture( creator.getTexture(), 64, 64 );
}

void PolygonRenderer::onRender()
{
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glEnable(GL_DEPTH_TEST);

	textureObject->apply(0);
	shaderObject.apply();

	shaderObject.setUniformMatrix("projectionMatrix", projectionMatrix);
	shaderObject.setUniformMatrix("modelviewMatrix", getModelviewMatrix());
	shaderObject.setUniformTexture("textureObject", *textureObject);
	shaderObject.setUniform("intensityScale", setting.backGroundIntensity);

	std::vector<double>& points = polygonModel.getVertices();
	//std::vector<double>& normals = polygonModel.getNormals();
	std::vector<double> texCoords = polygonModel.getTextureCoordinates();
	
	shaderObject.setVertex("position", points);
	//shaderObject.setVertexAttrib("normal", normals, 3);
	shaderObject.setVertexAttrib("texCoord", texCoords, 2);
	shaderObject.drawTriangles( points.size() / 3 );
	
	shaderObject.release();
	textureObject->release();

	glDisable( GL_DEPTH_TEST );
	glFlush();
}