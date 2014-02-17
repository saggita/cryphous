#include "GLee.h"

#include "PointSpriteRenderer.h"
#include "FrameBufferObject.h"
#include "RenderingCommand.h"

#include <cassert>
#include <ctime>

#include "GLSLUtility.h"

#include"VisualParticleConverter.h"

#include "ShaderCommand.h"

using namespace Crystal::Math;
using namespace Crystal::Shader;

PointSpriteRenderer::PointSpriteRenderer(float& size, float& alpha ) :
	size( size),
	alpha( alpha)
{
}

PointSpriteRenderer::~PointSpriteRenderer(void)
{
}

void PointSpriteRenderer::onRender()
{
	RenderingCommandStack commands;
	commands.push_back( new ColorBufferClearCommand(Color::Black()) );
	commands.push_back( new PointSpriteCommand() );
	commands.push_back( new DepthBufferClearCommand() );
	commands.push_back( new BlendingCommand() );
	
	ShaderCommandStack sCommands;
	sCommands.push_back( new UniformCommand("pointSize", size) );
	sCommands.push_back( new UniformMatrixCommand("projectionMatrix", projectionMatrix) );
	sCommands.push_back( new UniformMatrixCommand("modelviewMatrix", getModelviewMatrix() ) );
	sCommands.push_back( new VertexCommand( "position", positions ) );
	sCommands.push_back( new VertexAttribCommand( "color", colors, 4 ) );
	sCommands.push_back( new BindFlagCommand( "fragColor" ) );
	sCommands.push_back( new DrawPointsCommand( positions.size() / 3 ) );

	onRender( commands, sCommands );
}

void PointSpriteRenderer::onRender(RenderingCommandStack& commands, ShaderCommandStack& sCommands)
{
	commands.enable();

	if( !positions.empty() ) {
		sCommands.enable( &shaderObject );
	}
	
	commands.disable();
}

void PointSpriteRenderer::onInit()
{
	assert( GLSLUtility::hasNoError() );

	frameBufferObject = new FrameBufferObject(getWidth(), getHeight(), false);

	projectionMatrix.setPerspectiveMatrix(-0.5f, 0.5f, 0.0f, 1.0f, 0.01f, 100.0f );
	
	shaderObject.createShader("PointSprite");
}