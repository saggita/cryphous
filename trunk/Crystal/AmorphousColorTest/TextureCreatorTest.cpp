#include "StdAfx.h"
#include "TextureCreatorTest.h"

using namespace Amorphous::Color;

TextureCreatorTest::TextureCreatorTest(void)
{
	TextureCreator tCreator;
	tCreator.createTexture( 64 );
	tCreator.getTexture();
}


TextureCreatorTest::~TextureCreatorTest(void)
{
}
