#include "StdAfx.h"
#include "BlackBodyRadiatorXYZTest.h"

using namespace Amorphous::Color;

BlackBodyRadiatorXYZTest::BlackBodyRadiatorXYZTest(void)
{
	BlackBodyRadiatorXYZ* blackBodyRadiator = BlackBodyRadiatorXYZ::get();

	/*for( double temperature = 1000.0; temperature <= 10000.0; temperature += 1000.0 ) {
		const ColorRGBA& color = blackBodyRadiator->getColor( temperature );
	}*/

	for( double temperature = 1000.0; temperature <= 10000.0; temperature += 1000.0 ) {
		const ColorRGBA<>& color  = blackBodyRadiator->getColorFromCash( temperature );
	}
}

BlackBodyRadiatorXYZTest::~BlackBodyRadiatorXYZTest(void)
{
}
