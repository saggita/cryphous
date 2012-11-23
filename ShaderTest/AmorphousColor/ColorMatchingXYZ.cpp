#include "StdAfx.h"
#include "ColorMatchingXYZ.h"

#include <fstream>

using namespace Amorphous::Color;

ColorMatchingXYZ::ColorMatchingXYZ(void)
{
	setUpTable();
}

bool ColorMatchingXYZ::setUpTable()
{
	std::fstream stream( "../AmorphousColor/ciexyz64.csv", std::ios_base::in );

	MatchingTable table;
	while( stream ) {
		stream >> table.waveLength;
		stream.ignore();
		stream >> table.x;
		stream.ignore();
		stream >> table.y;
		stream.ignore();
		stream >> table.z;
		matchingTable.push_back( table );
	}
	return true;
}