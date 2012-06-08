#include "TextureCreator.h"

#include "../CrystalPhysics/Kernels3D.h"

#include <cstdlib>
#include <cmath>
#include <vector>

#include <boost/random.hpp>

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

	const double effectLength = size * 0.5;

	Kernels3D kernels( effectLength );

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

	bitmap = (unsigned char*)(malloc( sizeof(unsigned char) * size * size ) );

	for( int i = 0; i < size; ++i ) {
		for( int j = 0; j < size; ++j ) {
			const int bitmapIndex = i * size +j;
			bitmap[ bitmapIndex ] = bmpVec[i][j];
		}
	}
}

void TextureCreator::createNoiseTexture(const int size)
{
	destroyTexture();

	boost::variate_generator< boost::mt19937, boost::uniform_int<> > random( boost::mt19937(), boost::uniform_int<> (0, 255) );
	
	bitmap = (unsigned char*)(malloc( sizeof(unsigned char) * size * size ) );

	for( int i = 0; i < size; ++i ) {
		for( int j = 0; j < size; ++j ) {
			const int bitmapIndex = i * size +j;
			bitmap[ bitmapIndex ] = random();
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