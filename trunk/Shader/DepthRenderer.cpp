#include "GLee.h"

#include "DepthRenderer.h"

#include <cassert>
#include <ctime>

#include "GLSLUtility.h"
#include "FrameBufferObject.h"

#include "RenderingCommand.h"

#include "VisualParticleConverter.h"

#include "ShaderCommand.h"

using namespace Crystal::Math;
using namespace Crystal::Shader;

DepthRenderer::DepthRenderer(const float& size) :
	size( size)
{
}

DepthRenderer::~DepthRenderer(void)
{
}

void DepthRenderer::onRender()
{
	RenderingCommandStack commands;
	commands.push_back( new ColorBufferClearCommand(Color::Black()) );
	commands.push_back( new PointSpriteCommand() );
	commands.push_back( new DepthTestCommand() );
	commands.push_back( new DepthBufferClearCommand() );

	ShaderCommandStack sCommand;
	sCommand.push_back( new UniformCommand( "pointSize", size ) );
	sCommand.push_back( new UniformMatrixCommand( "projectionMatrix", projectionMatrix) );
	sCommand.push_back( new UniformMatrixCommand( "modelviewMatrix", getModelviewMatrix() ) );
	sCommand.push_back( new VertexCommand( "position", positions ) );
	sCommand.push_back( new VertexAttribCommand( "density", densities, 1 ) );
	sCommand.push_back( new BindFlagCommand( "fragColor" ) );
	sCommand.push_back( new DrawPointsCommand( positions.size() / 3 ) );

	onRender(commands, sCommand);
}

void DepthRenderer::onRender(RenderingCommandStack& commands, ShaderCommandStack& sCommands)
{
	commands.enable();

	if( !positions.empty() ) {
		sCommands.enable( &shaderObject );
	}

	commands.disable();
}

void DepthRenderer::onInit()
{
	assert( GLSLUtility::hasNoError() );

	frameBufferObject = new FrameBufferObject(getWidth(), getHeight(), false);

	projectionMatrix.setPerspectiveMatrix(-0.5f, 0.5f, 0.0f, 1.0f, 0.01f, 100.0f );
	
	shaderObject.createShader("Depth");
}