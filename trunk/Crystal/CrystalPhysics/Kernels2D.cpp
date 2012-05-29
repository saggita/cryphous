
#include "Kernels2D.h"

#include "../CrystalGeom/Tolerances.h"

#include <cmath>

using namespace Crystal::Geom;
using namespace Crystal::Physics;

Kernels2D::Kernels2D(const double effectLength):
Kernels( effectLength )
{
	setPoly6Constant();
	setPoly6ConstantGradient();
	setPoly6ConstantLaplacian();
	setSpikyConstantGradient();
	setViscosityConstantLaplacian();
}

Kernels2D::~Kernels2D(void)
{
}

void Kernels2D::setPoly6Constant()
{
	poly6Constant = 4.0 / ( Tolerances::getPI() * pow( effectLength, 8 ) );
}

void Kernels2D::setPoly6ConstantGradient()
{
	poly6ConstantGradient = 24.0 / ( Tolerances::getPI() * pow( effectLength, 8 ) );
}

void Kernels2D::setSpikyConstantGradient()
{
	spikyConstantGradient = 30.0 / ( Tolerances::getPI() * pow( effectLength, 5 ) );
}

void Kernels2D::setViscosityConstantLaplacian()
{
	viscosityConstantLaplacian = 20.0 / ( Tolerances::getPI() * pow( effectLength, 5 ) );
}