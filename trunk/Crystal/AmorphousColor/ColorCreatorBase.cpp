#include "StdAfx.h"
#include "ColorCreatorBase.h"

using namespace Crystal::Color;

ColorCreatorBase::ColorCreatorBase(void):
temperatureInterval(100.0)
{
}


ColorCreatorBase::~ColorCreatorBase(void)
{
}


ColorRGBA<> ColorCreatorBase::getColorFromCash(const double temperature) const
{
	size_t index = static_cast<size_t>( temperature / temperatureInterval );
	if( index >= colorCash.size() - 1 ) {
		return colorCash.back();
	}
	else if( index < 1 ) {
		return colorCash.front();
	}

	// è—]‚ð[0.0, 1.0]‚Ì”ÍˆÍ‚ÅŽæ“¾‚·‚é.
	const double mod = ( temperature - temperatureInterval * index ) / temperature;
	return colorCash[index].getBlended( colorCash[index+1], mod );
}

void ColorCreatorBase::createColorCash(const double minTemperature, const double maxTemperature)
{
	size_t size = static_cast<size_t>(maxTemperature / temperatureInterval);
	colorCash.assign( size, ColorRGBA<>(1.0, 0.0, 0.0) );
	for(double temperature = minTemperature; temperature < maxTemperature; temperature += temperatureInterval ) {
		const size_t index = static_cast<size_t>( temperature / temperatureInterval );
		colorCash[index] = getColor( temperature );
	}
}