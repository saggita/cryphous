#include "TextureCreator.h"

#include "../CrystalPhysics/Kernels3D.h"

#include <cstdlib>
#include <cmath>
#include <vector>

using namespace Crystal::Physics;
using namespace Crystal::Graphics;

TextureCreator::TextureCreator(void):
bitmap(0)
{
}

TextureCreator::~TextureCreator(void)
{
	destroyTexture();
}

void TextureCreator::createTexture(const int size)
{
	destroyTexture();

	std::vector< std::vector< unsigned char > > bmpVec;

	const int centerX = (int)(size * 0.5);
	const int centerY = (int)(size * 0.5);

	const float effectLength = size * 0.5f;

	Kernels3D kernels( effectLength );

	const float max = kernels.getPoly6Kernel( 0.0 );

	for( int i = 0; i < size; ++i ) {
		bmpVec.push_back( std::vector< unsigned char >() );
		for( int j = 0; j < size; ++j) {
			const float distSquare = std::pow( i - centerX, 2.0 ) + std::pow( j - centerY, 2.0 );
			float result = kernels.getPoly6Kernel( std::sqrt( distSquare ) ) / max * 0xff; 
			result = std::max( result, 0.0f );
			bmpVec[i].push_back( (unsigned char)( result) );
		}
	}

	bitmap = (unsigned char*)(malloc( sizeof(unsigned char) * size * size ) );

	for( int i = 0; i < size; ++i ) {
		for( int j = 0; j < size; ++j ) {
			const int bitmapIndex = i * size +j;
			bitmap[ bitmapIndex ] = bmpVec[i][j];
		}
	}
}

bool TextureCreator::destroyTexture()
{
	if( bitmap == 0 ) {
		return false;
	}
	
	delete[] bitmap;
	bitmap = 0;
	return true;
}