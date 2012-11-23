#include "../AmorphousGeom/AmorphousGeom.h"
#include "TextureCreator.h"

#include <cstdlib>
#include <cmath>
#include <vector>

using namespace Amorphous::Geom;
using namespace Amorphous::Color;

TextureCreator::TextureCreator(void):
bitmap(0)
{
}

TextureCreator::~TextureCreator(void)
{
}

void TextureCreator::createTexture(const int size)
{
	bitmap.clear();

	std::vector< std::vector< unsigned char > > bmpVec;

	const int centerX = (int)(size * 0.5);
	const int centerY = (int)(size * 0.5);

	const double effectLength = size * 0.5;

	Kernels2D kernels( effectLength );

	const double max = kernels.getPoly6Kernel( 0.0 );//getViscosityKernelLaplacian( 0.0 );
	
	for( int i = 0; i < size; ++i ) {
		bmpVec.push_back( std::vector< unsigned char >() );
		for( int j = 0; j < size; ++j) {
			const double distSquare = std::pow( i - centerX, 2.0 ) + std::pow( j - centerY, 2.0 );
			double result = kernels.getPoly6Kernel( std::sqrt( distSquare ) ) / max * 0xff; 
			if( result < 0.0 ) {
				result = 0.0;
			}
			bmpVec[i].push_back( (unsigned char)( result) );
		}
	}

	bitmap.resize( size * size );
	for( int i = 0; i < size; ++i ) {
		for( int j = 0; j < size; ++j ) {
			const int bitmapIndex = i * size +j;
			bitmap[ bitmapIndex ] = bmpVec[i][j];
		}
	}
}