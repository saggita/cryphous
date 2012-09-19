#include "RenderingCommand.h"

#include "../CrystalRenderer/PointSpriteFactory.h"
#include "../CrystalRenderer/PointSpriteRenderer.h"

#ifdef _OPENMP
#include <omp.h>
#endif

using namespace Crystal::Renderer;
using namespace Crystal::Command;

RenderingCommand::RenderingCommand(void)
{
}

Bitmap^ RenderingCommand::getImage(int width, int height)
{
	PointSpriteFactory factory(50, Color4d( 0.0, 0.0, 0.05f) );
	const std::vector<PointSprite*>& sprites = factory.getPointSprites();
	FrameBuffer buffer(width, height);
	PointSpriteRenderer renderer( buffer);

	#pragma omp parallel for	
	for( int i = 0; i < 10; ++i ) {
		for( int j = 0; j < 1000; ++j ) {
			renderer.render( *sprites[10], Point2d(i,j));
		}
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