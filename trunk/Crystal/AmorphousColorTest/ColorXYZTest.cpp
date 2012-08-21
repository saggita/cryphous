#include "StdAfx.h"
#include "ColorXYZTest.h"

using namespace Amorphous::Color;

ColorXYZTest::ColorXYZTest(void)
{
	ColorRGBA<> color4d( 1.0, 1.0, 1.0 );
	ColorXYZ colorXYZ( color4d );
	const ColorRGBA<>& converted = colorXYZ.convertToRGB();
	BOOST_CHECK( color4d == converted );
}

ColorXYZTest::~ColorXYZTest(void)
{
}
