#include "RenderingCommand.h"

#include "../CrystalPhysics/Simulation.h"
#include "../CrystalRenderer/PointSpriteFactory.h"
#include "../CrystalRenderer/PointSpriteRenderer.h"

#include "Command.h"

#ifdef _OPENMP
#include <omp.h>
#endif

using namespace Crystal::Geom;
using namespace Crystal::Renderer;
using namespace Crystal::Physics;
using namespace Crystal::Command;

RenderingCommand::RenderingCommand(Command^ mainCommand) :
	factory( new PointSpriteFactory(50, Color4d( 0.0, 0.0, 0.5f)) ),
	mainCommand( mainCommand)
{
}

RenderingCommand::~RenderingCommand()
{
	delete factory;
}

std::vector<Point2d> RenderingCommand::getPointsFromParticles()
{
	std::vector<Point2d> points;
	const ParticleVector& particles = mainCommand->factory->getParticles();
	for( unsigned int i = 0; i < particles.size(); ++i ) {
		points.push_back( Point2d( particles[i]->center.getX() * 100, particles[i]->center.getY() * 10 ) );
	}
	return points;
}

Bitmap^ RenderingCommand::getThicknessImage()
{
	const std::vector<PointSprite*>& sprites = factory->getPointSprites();
	FrameBuffer buffer(width, height);
	PointSpriteRenderer renderer( buffer);

	//#pragma omp parallel for	
	const std::vector<Point2d>& points = getPointsFromParticles();
	for( unsigned int i = 0; i < points.size(); ++i ) {
		renderer.renderThickness( *sprites[10], points[i] );
	}

	Bitmap^ bitmap = gcnew Bitmap( width, height);
	for( int x = 0; x < width; ++x ) {
		for( int y = 0; y < height; ++y ) {
			const Color4d& color = buffer.getColor( Point2d (x,y ) );
			const float red = std::min( color.red, 1.0f );
			const float green = std::min( color.green, 1.0f );
			const float blue = std::min( color.blue, 1.0f );
			bitmap->SetPixel( x, y, Color::FromArgb( int(red * 255), int(green * 255), int(blue * 255)) );
		}
	}
	return bitmap;
}

Bitmap^ RenderingCommand::getSurfaceImage()
{
	const std::vector<PointSprite*>& sprites = factory->getPointSprites();
	FrameBuffer buffer(width, height);
	PointSpriteRenderer renderer( buffer);

	//#pragma omp parallel for	
	const std::vector<Point2d>& points = getPointsFromParticles();
	for( unsigned int i = 0; i < points.size(); ++i ) {
		renderer.renderSurface( *sprites[10], points[i] );
	}

	Bitmap^ bitmap = gcnew Bitmap( width, height);
	for( int x = 0; x < width; ++x ) {
		for( int y = 0; y < height; ++y ) {
			const Color4d& color = buffer.getColor( Point2d (x,y ) );
			const float red = std::min( color.red, 1.0f );
			const float green = std::min( color.green, 1.0f );
			const float blue = std::min( color.blue, 1.0f );
			bitmap->SetPixel( x, y, Color::FromArgb( int(red * 255), int(green * 255), int(blue * 255)) );
		}
	}
	return bitmap;
}

Bitmap^ RenderingCommand::getNormalImage()
{
	const std::vector<PointSprite*>& sprites = factory->getPointSprites();
	FrameBuffer buffer(width, height);
	PointSpriteRenderer renderer( buffer);

	//#pragma omp parallel for	
	const std::vector<Point2d>& points = getPointsFromParticles();
	for( unsigned int i = 0; i < points.size(); ++i ) {
		renderer.renderSurface( *sprites[10], points[i] );
	}

	Bitmap^ bitmap = gcnew Bitmap( width, height);
	for( int x = 0; x < width; ++x ) {
		for( int y = 0; y < height; ++y ) {
			Vector3d normal = buffer.getNormal( Point2d (x,y ) );
			if( normal.isZero() ) {
				continue;
			}
			const float red = std::min( ::fabs(normal.getX()), 1.0f );
			const float green = std::min( ::fabs(normal.getY()), 1.0f );
			const float blue = std::min( ::fabs(normal.getZ()), 1.0f );
			bitmap->SetPixel( x, y, Color::FromArgb( int(red * 255), int(green * 255), int(blue * 255)) );
		}
	}
	return bitmap;
}

Bitmap^ RenderingCommand::getDepthImage()
{
	const std::vector<PointSprite*>& sprites = factory->getPointSprites();
	FrameBuffer buffer(width, height);
	PointSpriteRenderer renderer( buffer);

	//#pragma omp parallel for	
	const std::vector<Point2d>& points = getPointsFromParticles();
	for( unsigned int i = 0; i < points.size(); ++i ) {
		renderer.renderSurface( *sprites[10], points[i] );
	}

	Bitmap^ bitmap = gcnew Bitmap( width, height);
	for( int x = 0; x < width; ++x ) {
		for( int y = 0; y < height; ++y ) {
			const float depth = buffer.getDepth( Point2d (x,y ) ) / 100.0f;
			const float red = std::min( depth, 1.0f );
			const float green = std::min( depth, 1.0f );
			const float blue = std::min( depth, 1.0f );
			bitmap->SetPixel( x, y, Color::FromArgb( int(red * 255), int(green * 255), int(blue * 255)) );
		}
	}
	return bitmap;
}