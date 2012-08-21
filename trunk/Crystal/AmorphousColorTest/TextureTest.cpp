#include "StdAfx.h"
#include "TextureTest.h"

using namespace Amorphous::Color;

TextureTest::TextureTest(void)
{
	Pixels pixels;
	pixels.push_back( 1);
	pixels.push_back( 2);
	pixels.push_back( 3);
	pixels.push_back( 4);
	Texture textureX( pixels, 1, 1);

	BOOST_CHECK( textureX != Texture() );
	BOOST_CHECK( Texture() == Texture() );
}

TextureTest::~TextureTest(void)
{
}
