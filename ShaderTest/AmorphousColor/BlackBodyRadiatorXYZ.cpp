#include "StdAfx.h"
#include "BlackBodyRadiatorXYZ.h"

#include "ColorMatchingXYZ.h"
#include "ColorXYZ.h"

#include <cassert>
#include <boost/foreach.hpp>

using namespace Amorphous::Color;

BlackBodyRadiatorXYZ::BlackBodyRadiatorXYZ(void)
{
	createColorCash( 100.0, 20000.0 );
}

BlackBodyRadiatorXYZ::~BlackBodyRadiatorXYZ(void)
{
}

ColorRGBA<> BlackBodyRadiatorXYZ::getColor(const double temperature) const
{
	double x = 0.0;
	double y = 0.0;
	double z = 0.0;

	ColorMatchingXYZ colorMatching;
	const ColorMatchingXYZ::MatchingTableVector& tables = colorMatching.getMatchingTable();
	assert( !tables.empty() );

	const double waveLengthDiff = 5.0 * 1.0e-9;
	BOOST_FOREACH( const ColorMatchingXYZ::MatchingTable& table, tables ) {
		const double radiance = getRadiance( temperature, table.waveLength * 1.0e-9 ) * waveLengthDiff;
		x += radiance * table.x;
		y += radiance * table.y;
		z += radiance * table.z;
	}

	double c = 0.0;
	BOOST_FOREACH( const ColorMatchingXYZ::MatchingTable& table, tables ) {
		c += table.y * waveLengthDiff;
	}

	x /= c;
	y /= c;
	z /= c;

	ColorXYZ colorXYZ( x, y, z );
	ColorRGBA<> color = colorXYZ.convertToRGB();
	return color.normalize();
}

double BlackBodyRadiatorXYZ::getRadiance(const double temperature, const double waveLength) const
{
	// calculate radiance with Planck's formula.
	const double C1 = 3.7418e-16;
	const double C2 = 1.4388e-2;		

	return 2.0 * C1 / (std::pow(waveLength, 5) * ( std::exp( C2 / waveLength / temperature ) - 1.0 ) );
}