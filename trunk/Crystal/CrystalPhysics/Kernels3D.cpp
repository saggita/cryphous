
#include "Kernels3D.h"

#include "../CrystalGeom/Tolerances.h"
#include <cmath>

using namespace Crystal::Geom;
using namespace Crystal::Physics;

Kernels3D::Kernels3D(const double effectLength) :
Kernels( effectLength )
{
	setPoly6Constant();
	setPoly6ConstantGradient();
	setPoly6ConstantLaplacian();
	setSpikyConstantGradient();
	setViscosityConstantLaplacian();
}

Kernels3D::~Kernels3D(void)
{
}

void Kernels3D::setPoly6Constant()
{
	poly6Constant = 315.0 / (64.0 * Tolerances::getPI() * pow(effectLength,9) );
}

void Kernels3D::setPoly6ConstantGradient()
{
	poly6ConstantGradient = 945.0 / ( 32.0 * Tolerances::getPI() * pow(effectLength,9) );
}

void Kernels3D::setPoly6ConstantLaplacian()
{
	poly6ConstantLaplacian = 945.0 / ( 32 * Tolerances::getPI() * pow(effectLength,9 ) );
}

void Kernels3D::setSpikyConstantGradient()
{
	spikyConstantGradient = 45.0 / ( Tolerances::getPI() * pow(effectLength, 6 ) );
}

void Kernels3D::setViscosityConstantLaplacian()
{
	viscosityConstantLaplacian = 45.0 / ( Tolerances::getPI() * pow(effectLength, 6) );
}