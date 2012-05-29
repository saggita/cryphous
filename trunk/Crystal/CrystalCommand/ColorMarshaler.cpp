#include "ColorMarshaler.h"

#include "../CrystalGraphics/Color4d.h"

using namespace Crystal::Command;

ColorMarshaler::ColorMarshaler(void)
{
}

System::Drawing::Color ColorMarshaler::convertToDrawingColor(const Crystal::Graphics::Color4d& src)
{
	const int red = static_cast<int>(src.getRed() * 255);
	const int green = static_cast<int>(src.getGreen() * 255);
	const int blue = static_cast<int>(src.getBlue() * 255);
	return System::Drawing::Color::FromArgb( red, green, blue);
}

Crystal::Graphics::Color4d ColorMarshaler::convertToColor4d(System::Drawing::Color^ src)
{
	const double red = src->R / 255.0;
	const double green = src->G / 255.0;
	const double blue = src->B / 255.0;
	return Crystal::Graphics::Color4d( red, green, blue );
}