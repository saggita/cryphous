#include "StdAfx.h"
#include "ColorAdaptorTest.h"

using namespace Amorphous::Geom;
using namespace Amorphous::Color;

ColorAdaptorTest::ColorAdaptorTest(void)
{
	const double whitePointTemperature = 3000.0;
	const ColorRGBA<>& color = ColorAdaptor::get()->getColorFromCash( whitePointTemperature);
}

ColorAdaptorTest::~ColorAdaptorTest(void)
{
}
