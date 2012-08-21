#include "StdAfx.h"
#include "ColorRGBATest.h"

using namespace Amorphous::Color;

ColorRGBATest::ColorRGBATest(void)
{
	{
		ColorRGBA<> color( 1.0, 0.0, 0.0 );
		color *= 100.0;
		BOOST_CHECK( color == ColorRGBA<>( 100.0, 0.0, 0.0) );
		color /= 100.0;
		BOOST_CHECK( color == ColorRGBA<>( 1.0, 0.0, 0.0) );
	}

	{
		ColorRGBA<> color( 1.0e-10, 0.0, 0.0 );
		color.normalize();
		BOOST_CHECK( color == ColorRGBA<>( 1.0, 0.0, 0.0) );
	}

	{
		ColorRGBA<> color( 1.0e-10, 0.0, 0.0 );
		const ColorRGBA<>& normalized = color.getNormalize();
		BOOST_CHECK( normalized == ColorRGBA<>( 1.0, 0.0, 0.0 ) );
	}

	{
		ColorRGBA<> color( 0.1, 0.0, 0.1 );
		ColorRGBA<> scaledColor = color * 10.0;
		BOOST_CHECK( scaledColor == ColorRGBA<>( 1.0, 0.0, 1.0 ) );
	}

	{
		ColorRGBA<> colorX(1.0, 0.0, 0.0 );
		ColorRGBA<> colorY(0.0, 1.0, 0.0 );
		const ColorRGBA<>& blended = colorX.getBlended( colorY, 0.5 );
		BOOST_CHECK( blended.getRed() == blended.getGreen() );
		const ColorRGBA<>& weighted = colorX.getBlended( colorY, 0.1 );
		BOOST_CHECK( weighted.getRed() != weighted.getGreen() );
	}
}

ColorRGBATest::~ColorRGBATest(void)
{
}
