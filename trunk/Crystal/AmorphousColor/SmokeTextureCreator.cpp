#include "StdAfx.h"
#include "SmokeTextureCreator.h"

#include "../CrystalGeom/Tolerances.h"
#include <cmath>
#include <cassert>

using namespace Crystal::Geom;
using namespace Crystal::Color;

SmokeTextureCreator::SmokeTextureCreator(void) :
bitmap(0)
{
}

SmokeTextureCreator::~SmokeTextureCreator(void)
{
	this->destroyTexture();
}

double SmokeTextureCreator::calculateHenyeyGreensteinFunction(const double g, const double innerProduct)
{
	const double denominator =
		4.0 * Tolerances::getPI() * 2.0 * ( 2.0 + g * g ) * 
		std::pow( ( 1.0 + g * g - 2.0 * g * innerProduct ), 1.5 );

	assert( denominator != 0.0 );

	return 1.0 * 3.0 * ( 1.0 - std::pow(g,2) ) * (1.0 + std::pow( innerProduct, 2 ) ) / denominator;
}

bool SmokeTextureCreator::destroyTexture()
{
	if( bitmap == 0 ) {
		return false;
	}
	
	delete[] bitmap;
	bitmap = 0;
	return true;
}