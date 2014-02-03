#include "ScreenSpaceFluidRenderer.h"

#include "DepthRenderer.h"
#include "FrameBufferObject.h"
#include "TextureObject.h"

#include "RenderingCommand.h"
#include "ShaderCommand.h"

#include <cassert>

using namespace Crystal::Shader;

ScreenSpaceFluidRenderer::ScreenSpaceFluidRenderer()
{
}

ScreenSpaceFluidRenderer::~ScreenSpaceFluidRenderer()
{
}

void ScreenSpaceFluidRenderer::onInit()
{
	frameBufferObject = new FrameBufferObject(getWidth(), getHeight(), false);

	shaderObject.createShader("ScreenSpaceFluid");

	projectionMatrix.setOrthogonalMatrix( 0.0, 1.0, 0.0, 1.0, -1.0, 1.0 );
}

void ScreenSpaceFluidRenderer::onRender()
{
	RenderingCommandStack commands;
	Color color( 0.8f, 0.8f, 0.9f, 1.0f );
	commands.push_back( new ColorBufferClearCommand(color) );
	commands.push_back( new DepthBufferClearCommand() );
	commands.push_back( new BlendingCommand() );

	std::vector<float> points(12);
	points[0] = 0.0; points[1] = 1.0; points[2] = 0.0;
	points[3] = 0.0; points[4] = 0.0; points[5] = 0.0;
	points[6] = 1.0; points[7] = 0.0; points[8] = 0.0;
	points[9] = 1.0; points[10] = 1.0; points[11] = 0.0;

	ShaderCommandStack sCommand;
	sCommand.push_back( new UniformMatrixCommand("projectionMatrix", projectionMatrix) );
	sCommand.push_back( new UniformMatrixCommand("modelviewMatrix", GLSLMatrix::IdentityMatrix() ) );
	sCommand.push_back( new UniformCommand("near", 0.01f) );
	sCommand.push_back( new UniformCommand("far", 100.0f) );
	sCommand.push_back( new UniformTextureCommand("depthTexture", depthSmoothingTexture) );
	sCommand.push_back( new UniformTextureCommand("thicknessTexture", thicknessTexture) );
	sCommand.push_back( new UniformTextureCommand("backgroundTexture", backgroundTexture) );
	sCommand.push_back( new VertexCommand("position", points ) );
	sCommand.push_back( new BindFlagCommand("fragColor") );
	sCommand.push_back( new DrawQuadsCommand( 4 ) );

	onRender( commands, sCommand );
}

#include "TextureObjectStack.h"

void ScreenSpaceFluidRenderer::onRender(RenderingCommandStack& commands, ShaderCommandStack& sCommands)
{
	commands.enable();

	TextureObjectStack textures;

	textures.push_back( depthSmoothingTexture );
	textures.push_back( thicknessTexture );
	textures.push_back( backgroundTexture );

	textures.apply();

	sCommands.enable( &shaderObject );

	textures.release();

	commands.disable();
}