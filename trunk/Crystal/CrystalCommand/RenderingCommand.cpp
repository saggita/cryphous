#include "RenderingCommand.h"

#include "../CrystalRenderer/PointSpriteFactory.h"
#include "../CrystalRenderer/PointSpriteRenderer.h"

using namespace Crystal::Renderer;
using namespace Crystal::Command;

RenderingCommand::RenderingCommand(void)
{
}

Bitmap^ RenderingCommand::getImage(int width, int height)
{
	//PointSpriteFactory factory(50);
	//const std::vector<PointSprite*>& sprites = factory.getPointSprites();
	FrameBuffer buffer(width, height);
	PointSprite sprite = PointSprite(5, Color4d(0.0, 0.0, 1.0));
	PointSpriteRenderer renderer( buffer);
	renderer.render( sprite, Point2d(10,10));
	PointSprite sprite2 = PointSprite(10, Color4d(1.0, 0.0, 0.0));
	renderer.render( sprite2, Point2d( 50, 50 ) );

	Bitmap^ bitmap = gcnew Bitmap( width, height);
	for( int x = 0; x < width; ++x ) {
		for( int y = 0; y < height; ++y ) {
			const Color4d& color = buffer.getColor( Point2d (x,y ) );
			bitmap->SetPixel( x, y, Color::FromArgb(color.red * 255, color.green * 255, color.blue * 255) );
		}
	}
	return bitmap;
}