#include "OnScreenRenderer.h"

#include "OffScreenRendererBase.h"
#include "FrameBufferObject.h"
#include "TextureObject.h"

#include <cassert>

using namespace Crystal::Shader;

OnScreenRenderer::OnScreenRenderer()
{
}

OnScreenRenderer::~OnScreenRenderer()
{
}

void OnScreenRenderer::render()
{
	assert( GL_NO_ERROR == glGetError() );
	glViewport( 0, 0, getWidth() , getHeight() );
	assert( GL_NO_ERROR == glGetError() );
	onRender();
}

void OnScreenRenderer::idle()
{
	onIdle();
}

void OnScreenRenderer::onInit()
{
	shaderObject.createShader("Quad");

	projectionMatrix.setOrthogonalMatrix( 0.0, 1.0, 0.0, 1.0, -1.0, 1.0 );
}

#include "RenderingCommand.h"
#include "ShaderCommand.h"

void OnScreenRenderer::onRender()
{
	RenderingCommandStack commands;
	commands.push_back( new ColorBufferClearCommand( Color::Black() ) );
	commands.push_back( new DepthBufferClearCommand() );
	commands.push_back( new DepthTestCommand() );

	std::vector<float> points(12);
	points[0] = 0.0; points[1] = 1.0; points[2] = 0.0;
	points[3] = 0.0; points[4] = 0.0; points[5] = 0.0;
	points[6] = 1.0; points[7] = 0.0; points[8] = 0.0;
	points[9] = 1.0; points[10] = 1.0; points[11] = 0.0;

	ShaderCommandStack sCommands;
	sCommands.push_back( new UniformMatrixCommand("projectionMatrix", projectionMatrix) );
	sCommands.push_back( new UniformMatrixCommand("modelviewMatrix", GLSLMatrix::IdentityMatrix() ) );
	sCommands.push_back( new UniformTextureCommand( "offScreenTexture", texture ) );
	sCommands.push_back( new VertexCommand( "position", points ) );
	sCommands.push_back( new DrawQuadsCommand( 4 ) );

	onRender( commands, sCommands );
}

void OnScreenRenderer::onRender(RenderingCommandStack& commands, ShaderCommandStack& sCommands)
{
	commands.enable();

	texture->apply( 0 );

	sCommands.enable( &shaderObject );

	texture->release();

	commands.disable();
}