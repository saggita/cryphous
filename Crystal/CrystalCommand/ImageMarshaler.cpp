#include "ImageMarshaler.h"

#include "../CrystalGraphics/Color4d.h"
#include "../CrystalGraphics/Texture.h"

#include <cassert>

using namespace Crystal::Command;

System::Drawing::Bitmap^ ImageMarshaler::convertToBitmap(const Crystal::Graphics::Texture &src)
{
	System::Drawing::Bitmap^ bmp = gcnew System::Drawing::Bitmap( src.getWidth(), src.getHeight() );

	const Crystal::Graphics::Pixels& pixels = src.getPixels();
	Crystal::Graphics::Pixels::const_iterator iter = pixels.begin();
	for( int y = src.getHeight()-1; y>=0; y-- ) {
		for ( int x = 0; x < src.getWidth(); x++ ) {
			const int red = *iter++;
			const int green = *iter++;
			const int blue = *iter++;
			++iter;	// ignore alpha.
			System::Drawing::Color newColor = System::Drawing::Color::FromArgb( red, green, blue );
			bmp->SetPixel( x, y, newColor );
		}
	}

	return bmp;
}

Crystal::Graphics::Texture ImageMarshaler::convertToTexture(System::Drawing::Bitmap ^src)
{
	Crystal::Graphics::Pixels pixels;
	for( int y = src->Height - 1; y >= 0; y-- ) {
		for( int x = 0; x < src->Width; x++ ) {
			System::Drawing::Color color = src->GetPixel( x, y );
			pixels.push_back( color.R );
			pixels.push_back( color.G );
			pixels.push_back( color.B );
			pixels.push_back( color.A );
		}
	}
	return Crystal::Graphics::Texture( pixels, src->Width, src->Height );
}