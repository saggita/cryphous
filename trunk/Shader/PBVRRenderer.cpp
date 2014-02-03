#include "GLee.h"

#include "PBVRRenderer.h"
#include "FrameBufferObject.h"

#include <cassert>
#include <ctime>

#include "GLSLUtility.h"

#include "RenderingCommand.h"

#include"VisualParticleConverter.h"

using namespace Crystal::Math;
using namespace Crystal::Shader;

PBVRRenderer::PBVRRenderer(float& size, float& alpha ) :
	size( size),
	alpha( alpha)
{
}

PBVRRenderer::~PBVRRenderer(void)
{
}

#include "ShaderCommand.h"

void PBVRRenderer::onRender()
{
	RenderingCommandStack commands;

	Color color( 0.8f, 0.8f, 0.9f, 1.0f );

	commands.push_back( new ColorBufferClearCommand(color) );
	commands.push_back( new PointSpriteCommand() );
	commands.push_back( new DepthBufferClearCommand() );
	commands.push_back( new BlendingCommand() );

	commands.enable();

	if( !positions.empty() ) {
		ShaderCommandStack sCommand;
		sCommand.push_back( new UniformCommand( "pointSize", size ) );
		sCommand.push_back( new UniformMatrixCommand( "projectionMatrix", projectionMatrix) );
		sCommand.push_back( new UniformMatrixCommand( "modelviewMatrix", getModelviewMatrix() ) );
		sCommand.push_back( new VertexCommand( "position", positions ) ); 
		sCommand.push_back( new VertexAttribCommand( "color", colors, 4 ) );
		sCommand.push_back( new BindFlagCommand( "fragColor" ) );
		sCommand.push_back( new DrawPointsCommand( positions.size() / 3 ) );
		sCommand.enable( &shaderObject );
	}

	commands.disable();
}

void PBVRRenderer::onInit()
{
	assert( GLSLUtility::hasNoError() );

	frameBufferObject = new FrameBufferObject(getWidth(), getHeight(), false);

	projectionMatrix.setPerspectiveMatrix(-0.5f, 0.5f, 0.0f, 1.0f, 0.01f, 100.0f );
	
	shaderObject.createShader("PBVR");
}