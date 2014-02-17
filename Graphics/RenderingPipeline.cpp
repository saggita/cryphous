#include "RenderingPipeline.h"

#include "FrameBufferObject.h"
#include "TextureObject.h"

#include "Bitmap.h"
#include "Camera.h"

#include "RenderingCommand.h"
#include "ShaderCommand.h"
#include "TextureObjectStack.h"

#include "Vertex.h"

#include <cassert>

using namespace Crystal::Graphics;

std::vector<float> getQuadPoints()
{
	VertexCollection vertices;
	vertices.push_back( Vertex( 0.0, 1.0, 0.0 ) );
	vertices.push_back( Vertex( 0.0, 0.0, 0.0 ) );
	vertices.push_back( Vertex( 1.0, 0.0, 0.0 ) );
	vertices.push_back( Vertex( 1.0, 1.0, 0.0 ) );
	return vertices.toArray();
}

void renderOnScreen( const int width, const int height, TextureObject* texture, ShaderObject& shaderObject )
{
	assert( GL_NO_ERROR == glGetError() );

	GLSLMatrix projectionMatrix = GLSLMatrix::OrthogonalMatrix( 0.0, 1.0, 0.0, 1.0, -1.0, 1.0 );

	glViewport( 0, 0, width, height );
	
	RenderingCommandStack commands;
	commands.push_back( new ColorBufferClearCommand( Color::Black() ) );
	commands.push_back( new DepthBufferClearCommand() );
	commands.push_back( new DepthTestCommand() );

	std::vector<float> points = getQuadPoints();
	ShaderCommandStack sCommands;
	sCommands.push_back( new UniformMatrixCommand("projectionMatrix", projectionMatrix ) );
	sCommands.push_back( new UniformMatrixCommand("modelviewMatrix", GLSLMatrix::IdentityMatrix() ) );
	sCommands.push_back( new UniformTextureCommand( "offScreenTexture", texture ) );
	sCommands.push_back( new VertexCommand( "position", points ) );
	sCommands.push_back( new DrawQuadsCommand( 4 ) );

	commands.enable();

	texture->apply( 0 );

	sCommands.enable( &shaderObject );

	texture->release();

	commands.disable();

	assert( GL_NO_ERROR == glGetError() );
}

void RenderingPipeline::build(const int width, const int height)
{
	bitmap.readFromFile("../Shaders/checker.bmp");

	pointSprite.build( "PointSprite", width, height );
	thickness.build( "Thickness", width, height );
	depth.build( "Depth", width, height );
	depthSmoothing.build( "Smoothing", width, height );
	thicknessSmoothing.build( "Smoothing", width, height );
	fluid.build( "ScreenSpaceFluid", width, height );
	normal.build( "Normal", width, height );
	scene.build( "Scene", width, height );

	backgroundTexture.init( bitmap.getColors(), bitmap.getWidth(), bitmap.getHeight() );

	onScreenShader.build( "Quad" );

	pointSprite.pushCommand( new ColorBufferClearCommand( Color::White() ) );
	pointSprite.pushCommand( new PointSpriteCommand() );
	pointSprite.pushCommand( new DepthTestCommand() );
	pointSprite.pushCommand( new DepthBufferClearCommand() );

	pointSprite.render( width, height );

	depth.pushCommand( new ColorBufferClearCommand(Color::Black()) );
	depth.pushCommand( new PointSpriteCommand() );
	depth.pushCommand( new DepthTestCommand() );
	depth.pushCommand( new DepthBufferClearCommand() );

	thickness.pushCommand( new ColorBufferClearCommand(Color::Black() ) );
	thickness.pushCommand( new PointSpriteCommand() );
	thickness.pushCommand( new DepthBufferClearCommand() );
	thickness.pushCommand( new BlendingCommand() );

	depthSmoothing.pushCommand( new ColorBufferClearCommand( Color::Black() ) );
	depthSmoothing.pushCommand( new DepthBufferClearCommand() );

	thicknessSmoothing.pushCommand( new ColorBufferClearCommand( Color::Black() ) );
	thicknessSmoothing.pushCommand( new DepthBufferClearCommand() );

	//Color color( 0.8f, 0.8f, 0.9f, 1.0f );

	fluid.pushCommand( new ColorBufferClearCommand( Color::Black() ) );
	fluid.pushCommand( new DepthBufferClearCommand() );
	fluid.pushCommand( new BlendingCommand() );

	normal.pushCommand( new ColorBufferClearCommand( Color::Black() ) );
	normal.pushCommand( new DepthBufferClearCommand() );

	scene.pushCommand( new ColorBufferClearCommand( Color::Black() ) );
	scene.pushCommand( new DepthBufferClearCommand() );
	scene.pushCommand( new DepthTestCommand() );
	
	selectedTexture = pointSprite.getTexture();
}

void RenderingPipeline::render(const int width, const int height, const std::vector< float >& positions, const std::vector< float >& colors, Camera* camera, const Param& param )
{
	const float nearZ = 0.01f;
	const float farZ = 10.0f;
	const GLSLMatrix perspectiveMatrix = GLSLMatrix::PerspectiveMatrix( -0.5f, 0.5f, 0.0f, 1.0f, nearZ, farZ );

	pointSprite.clearShaders();
	pointSprite.pushShader( new UniformCommand("pointSize", param.pointSize ) );
	pointSprite.pushShader( new UniformMatrixCommand("projectionMatrix", perspectiveMatrix ) );
	pointSprite.pushShader( new UniformMatrixCommand("modelviewMatrix", camera->getModelviewMatrix() ) );
	pointSprite.pushShader( new VertexCommand( "position", positions ) );
	pointSprite.pushShader( new VertexAttribCommand( "color", colors, 4 ) );
	pointSprite.pushShader( new BindFlagCommand( "fragColor" ) );
	pointSprite.pushShader( new DrawPointsCommand( positions.size() / 3 ) );

	pointSprite.render( width, height );

	depth.clearShaders();
	depth.pushShader( new UniformCommand( "pointSize", param.pointSize ) );
	depth.pushShader( new UniformMatrixCommand( "projectionMatrix", perspectiveMatrix ) );
	depth.pushShader( new UniformMatrixCommand( "modelviewMatrix", camera->getModelviewMatrix() ) );
	depth.pushShader( new VertexCommand( "position", positions ) );
	depth.pushShader( new BindFlagCommand( "fragColor" ) );
	depth.pushShader( new DrawPointsCommand( positions.size() / 3 ) );

	depth.render( width, height  );

	std::vector<float> points = getQuadPoints();

	GLSLMatrix projectionMatrix = GLSLMatrix::OrthogonalMatrix( 0.0, 1.0, 0.0, 1.0, -1.0, 1.0 );	

	depthSmoothing.clearShaders();
	depthSmoothing.pushShader( new UniformMatrixCommand( "projectionMatrix", projectionMatrix) );
	depthSmoothing.pushShader( new UniformMatrixCommand( "modelviewMatrix", GLSLMatrix::IdentityMatrix() ) );
	depthSmoothing.pushShader( new UniformTextureCommand( "depthTexture", thickness.getTexture() ) );
	depthSmoothing.pushShader( new UniformIntCommand( "filterRadius", param.filterRadius ) );
	depthSmoothing.pushShader( new VertexCommand( "position", points ) ); 
	depthSmoothing.pushShader( new BindFlagCommand( "fragColor" ) );
	depthSmoothing.pushShader( new DrawQuadsCommand( 4 ) );

	depthSmoothing.clearTextures();
	depthSmoothing.pushTexture( depth.getTexture() );
	depthSmoothing.render( width, height );
	
	thickness.clearShaders();
	thickness.pushShader( new UniformCommand( "pointSize", param.pointSize ) );
	thickness.pushShader( new UniformMatrixCommand( "projectionMatrix", perspectiveMatrix ) );
	thickness.pushShader( new UniformMatrixCommand( "modelviewMatrix", camera->getModelviewMatrix() ) );
	thickness.pushShader( new VertexCommand( "position", positions ) );
	thickness.pushShader( new BindFlagCommand( "fragColor" ) );
	thickness.pushShader( new DrawPointsCommand( positions.size() / 3 ) );

	thickness.render( width, height );

	thicknessSmoothing.clearShaders();
	thicknessSmoothing.pushShader( new UniformMatrixCommand( "projectionMatrix", projectionMatrix) );
	thicknessSmoothing.pushShader( new UniformMatrixCommand( "modelviewMatrix", GLSLMatrix::IdentityMatrix() ) );
	thicknessSmoothing.pushShader( new UniformTextureCommand( "depthTexture", thickness.getTexture() ) );
	thicknessSmoothing.pushShader( new UniformIntCommand( "filterRadius", param.filterRadius ) );
	thicknessSmoothing.pushShader( new VertexCommand( "position", points ) ); 
	thicknessSmoothing.pushShader( new BindFlagCommand( "fragColor" ) );
	thicknessSmoothing.pushShader( new DrawQuadsCommand( 4 ) );

	thicknessSmoothing.clearTextures();
	thicknessSmoothing.pushTexture( thickness.getTexture() );
	thicknessSmoothing.render( width, height );

	normal.clearShaders();
	normal.pushShader( new UniformMatrixCommand("projectionMatrix", projectionMatrix) );
	normal.pushShader( new UniformMatrixCommand("modelviewMatrix", GLSLMatrix::IdentityMatrix() ) );
	normal.pushShader( new UniformIntCommand("width", width) );
	normal.pushShader( new UniformIntCommand("height", height) );
	normal.pushShader( new UniformCommand("near", nearZ) );
	normal.pushShader( new UniformCommand("far", farZ) );
	normal.pushShader( new UniformTextureCommand("depthTexture", depthSmoothing.getTexture() ) );
	normal.pushShader( new VertexCommand("position", points ) );
	normal.pushShader( new BindFlagCommand("fragColor") );
	normal.pushShader( new DrawQuadsCommand( 4 ) );

	normal.clearTextures();
	normal.pushTexture( depthSmoothing.getTexture() );
	normal.render( width, height );

	const float minX = -0.5f;
	const float maxX =  0.5;

	const float minY =  0.0f;
	const float maxY =  0.2f;

	const float minZ = -0.5f;
	const float maxZ =  0.5f;

	VertexCollection vertices;
	vertices.push_back( Vertex( minX, minY, minZ ) );
	vertices.push_back( Vertex( minX, maxY, minZ ) );
	vertices.push_back( Vertex( maxX, maxY, minZ ) );
	vertices.push_back( Vertex( maxX, minY, minZ ) );

	vertices.push_back( Vertex( maxX, minY, maxZ ) );
	vertices.push_back( Vertex( maxX, minY, minZ ) );
	vertices.push_back( Vertex( maxX, maxY, minZ ) );
	vertices.push_back( Vertex( maxX, maxY, maxZ ) );

	vertices.push_back( Vertex( minX, minY, maxZ ) );
	vertices.push_back( Vertex( minX, minY, minZ ) );
	vertices.push_back( Vertex( minX, maxY, minZ ) );
	vertices.push_back( Vertex( minX, maxY, maxZ ) );

	vertices.push_back( Vertex( minX, maxY, maxZ ) );
	vertices.push_back( Vertex( minX, maxY, minZ ) );
	vertices.push_back( Vertex( maxX, maxY, minZ ) );
	vertices.push_back( Vertex( maxX, maxY, maxZ ) );

	vertices.push_back( Vertex( minX, minY, maxZ ) );
	vertices.push_back( Vertex( minX, minY, minZ ) );
	vertices.push_back( Vertex( maxX, minY, minZ ) );
	vertices.push_back( Vertex( maxX, minY, maxZ ) );

	ColorCollection vertColors;
	vertColors.push_back( Color::White() );
	vertColors.push_back( Color::White() );
	vertColors.push_back( Color::White() );
	vertColors.push_back( Color::White() );

	vertColors.push_back( Color::Red() );
	vertColors.push_back( Color::Red() );
	vertColors.push_back( Color::Red() );
	vertColors.push_back( Color::Red() );

	vertColors.push_back( Color::Green() );
	vertColors.push_back( Color::Green() );
	vertColors.push_back( Color::Green() );
	vertColors.push_back( Color::Green() );

	vertColors.push_back( Color::Blue() );
	vertColors.push_back( Color::Blue() );
	vertColors.push_back( Color::Blue() );
	vertColors.push_back( Color::Blue() );

	vertColors.push_back( Color::Yellow() );
	vertColors.push_back( Color::Yellow() );
	vertColors.push_back( Color::Yellow() );
	vertColors.push_back( Color::Yellow() );

	scene.clearShaders();
	scene.pushShader( new UniformMatrixCommand( "projectionMatrix", perspectiveMatrix ) );
	scene.pushShader( new UniformMatrixCommand( "modelviewMatrix", camera->getModelviewMatrix() ) );
	scene.pushShader( new VertexCommand( "position", vertices.toArray() ) ); 
	scene.pushShader( new VertexAttribCommand( "color", vertColors.toArray4(), 4 ) );
	scene.pushShader( new BindFlagCommand( "fragColor" ) );
	scene.pushShader( new DrawQuadsCommand( vertices.size() ) );

	scene.render( width, height );


	std::vector< float > eyePosition(3);
	eyePosition[0] = camera->cameraX;
	eyePosition[1] = camera->cameraY;
	eyePosition[2] = camera->cameraX;

	const std::vector< float > color = param.fluidColor.toArray3();
	const std::vector<float> dColor = param.diffuseColor.toArray3();
	const std::vector<float> sColor = param.specularColor.toArray3();

	fluid.clearShaders();
	fluid.pushShader( new UniformMatrixCommand("projectionMatrix", projectionMatrix) );
	fluid.pushShader( new UniformMatrixCommand("modelviewMatrix", GLSLMatrix::IdentityMatrix() ) );
	fluid.pushShader( new UniformTextureCommand("normalTexture", normal.getTexture() ) );
	fluid.pushShader( new UniformTextureCommand("thicknessTexture", thicknessSmoothing.getTexture() ) );
	fluid.pushShader( new UniformTextureCommand("backgroundTexture", scene.getTexture() ) );//&backgroundTexture) );
	fluid.pushShader( new UniformArrayCommand( "eyePosition", eyePosition ) );
	fluid.pushShader( new UniformArrayCommand( "lightPos", param.lightPosition.toArray() ) );
	fluid.pushShader( new UniformCommand( "alpha", param.alpha ) );
	fluid.pushShader( new UniformArrayCommand( "fluidColor", color ) );
	fluid.pushShader( new UniformArrayCommand("diffuseColor", dColor ) );
	fluid.pushShader( new UniformArrayCommand("specularColor", sColor ) );
	fluid.pushShader( new VertexCommand("position", points ) );
	fluid.pushShader( new BindFlagCommand("fragColor") );
	fluid.pushShader( new DrawQuadsCommand( 4 ) );

	fluid.clearTextures();
	fluid.pushTexture( normal.getTexture() );
	fluid.pushTexture( thicknessSmoothing.getTexture() );
	fluid.pushTexture( scene.getTexture() );
	fluid.render( width, height );

	::renderOnScreen( width, height, selectedTexture, onScreenShader );
}