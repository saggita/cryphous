#include "TextureCreator.h"

#include "ImprovedPerlinNoise.h"

#include <cstdlib>
#include <cmath>
#include <vector>

#include "../CrystalPhysics/Kernels3D.h"

using namespace Crystal::Physics;
using namespace Crystal::Shader;

TextureCreator::TextureCreator(void):
bitmap(0)
{
}

TextureCreator::~TextureCreator(void)
{
}

void TextureCreator::createTexture(const int size,const bool addNoise)
{
	bitmap.clear();

	std::vector< std::vector< unsigned char > > bmpVec;

	const int centerX = (int)(size * 0.5);
	const int centerY = (int)(size * 0.5);

	const float effectLength = size * 0.5f;

	Crystal::Physics::Kernels3D kernels( effectLength );

	const double max = kernels.getPoly6Kernel( 0.0 );//getViscosityKernelLaplacian( 0.0 );
	
	for( int i = 0; i < size; ++i ) {
		bmpVec.push_back( std::vector< unsigned char >() );
		for( int j = 0; j < size; ++j) {
			const float distSquare = std::pow( i - centerX, 2.0f ) + std::pow( j - centerY, 2.0f );
			float result = kernels.getPoly6Kernel( std::sqrt( distSquare ) ) / max * 0xff; 
			if( result < 0.0 ) {
				result = 0.0;
			}
			bmpVec[i].push_back( (unsigned char)( result) );
		}
	}

	bitmap.resize( size * size );
	ImprovedPerlinNoise noise;
	for( int i = 0; i < size; ++i ) {
		for( int j = 0; j < size; ++j ) {
			const int bitmapIndex = i * size +j;
			bitmap[ bitmapIndex ] = bmpVec[i][j];
			if( addNoise ) {
				unsigned char noiseVal = static_cast<unsigned char>(noise.getNoise(i,j,0.0));
				bitmap[bitmapIndex] *= noiseVal;
			}
		}
	}
}