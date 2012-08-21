#include "StdAfx.h"
#include "ColorAdaptor.h"

#include "ColorRGBA.h"
#include "ColorXYZ.h"
#include "ColorLMS.h"
#include "BlackBodyRadiatorXYZ.h"

#include <cassert>

using namespace Crystal::Geom;
using namespace Crystal::Color;

ColorAdaptor::ColorAdaptor(const double whitePointTemperature) :
whitePointTemperature( whitePointTemperature)
{
	createColorCash( 100.0, 20000.0 );
}

ColorAdaptor::~ColorAdaptor(void)
{
}

ColorRGBA<> ColorAdaptor::getColor(const double temperature) const
{
	const ColorRGBA<>& rawRGB = BlackBodyRadiatorXYZ::get()->getColorFromCash( temperature );
	const ColorXYZ rawXYZ( rawRGB );
	const Vector3d vector( rawXYZ.getX(), rawXYZ.getY(), rawXYZ.getZ() );
	const Vector3d& resultVector = getAdaptMatrix() * vector;
	const ColorXYZ result( resultVector.getX(), resultVector.getY(), resultVector.getZ() );
	return result.convertToRGB().normalize();
}

Matrix3d ColorAdaptor::getAdaptMatrix() const
{
	return ColorLMS::getToXYZMatrix() * getWhitePointLMSMatrix() * ColorLMS::getToLMSMatrix();
}

ColorLMS ColorAdaptor::getWhitePointLMS() const
{
	const ColorRGBA<>& whitePointRGB = BlackBodyRadiatorXYZ::get()->getColorFromCash( whitePointTemperature );
	const ColorXYZ& maxColorXYZ( whitePointRGB );
	return ColorLMS( maxColorXYZ);
}

Matrix3d ColorAdaptor::getWhitePointLMSMatrix() const
{
	const ColorLMS& lms = getWhitePointLMS();
	return Matrix3d( 1.0 / lms.getL(), 0.0, 0.0,
		0.0, 1.0 / lms.getM(), 0.0,
		0.0, 0.0, 1.0 / lms.getS() );
}