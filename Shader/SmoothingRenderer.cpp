#include "SmoothingRenderer.h"

#include "DepthRenderer.h"
#include "FrameBufferObject.h"
#include "TextureObject.h"

#include <cassert>

#include "RenderingCommand.h"
#include "ShaderCommand.h"

using namespace Crystal::Shader;

SmoothingRenderer::SmoothingRenderer()
{
}

SmoothingRenderer::~SmoothingRenderer()
{
}

void SmoothingRenderer::onInit()
{
	frameBufferObject = new FrameBufferObject(getWidth(), getHeight(), false);

	shaderObject.createShader("DepthSmoothing");

	projectionMatrix.setOrthogonalMatrix( 0.0, 1.0, 0.0, 1.0, -1.0, 1.0 );
}

void SmoothingRenderer::onRender()
{
//	glDisable( GL_DEPTH_TEST );

	RenderingCommandStack commands;
	commands.push_back( new ColorBufferClearCommand(Color::Black()) );
	commands.push_back( new DepthBufferClearCommand() );

	commands.enable();

	TextureObject& textureObject = *depthTexture;
	textureObject.apply( 0 );

	std::vector<float> points(12);
	points[0] = 0.0; points[1] = 1.0; points[2] = 0.0;
	points[3] = 0.0; points[4] = 0.0; points[5] = 0.0;
	points[6] = 1.0; points[7] = 0.0; points[8] = 0.0;
	points[9] = 1.0; points[10] = 1.0; points[11] = 0.0;

	ShaderCommandStack sCommand;

	sCommand.push_back( new UniformMatrixCommand( "projectionMatrix", projectionMatrix) );
	sCommand.push_back( new UniformMatrixCommand( "modelviewMatrix", GLSLMatrix::IdentityMatrix() ) );
	sCommand.push_back( new UniformTextureCommand( "depthTexture", &textureObject ) );
	sCommand.push_back( new VertexCommand( "position", points ) ); 
	sCommand.push_back( new BindFlagCommand( "fragColor" ) );
	sCommand.push_back( new DrawQuadsCommand( 4 ) );
	
	onRender( sCommand );

	textureObject.release();

	commands.disable();

//	glEnable( GL_DEPTH_TEST );
}

void SmoothingRenderer::onRender(ShaderCommandStack& sCommand)
{
	sCommand.enable( &shaderObject );
}