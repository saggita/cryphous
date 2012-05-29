#include "Kernels.h"

#include "../CrystalGeom/Point3d.h"
#include "../CrystalGeom/Vector3d.h"
#include "../CrystalGeom/Tolerances.h"

#include <cmath>
#include <cassert>

using namespace Crystal::Geom;
using namespace Crystal::Physics;

Kernels::Kernels(const double effectLength) :
effectLength( effectLength )
{
}

double Kernels::getPoly6Kernel(const double distance)
{
	return getPoly6Constant() * pow( effectLength * effectLength - distance * distance, 3 );
}

Vector3d Kernels::getPoly6KernelGradient(const Vector3d& distanceVector)
{
	const double distance = distanceVector.getLength();
	const double factor = getPoly6ConstantGradient() * pow( effectLength * effectLength - distance * distance, 2 );
	return distanceVector * factor;
}

double Kernels::getPoly6KernelLaplacian(const double distance )
{
	return getPoly6ConstantLaplacian() * ( effectLength * effectLength - distance * distance ) 
		* ( 42.0 * distance * distance - 18.0 * effectLength * effectLength );
}

Vector3d Kernels::getSpikyKernelGradient(const Vector3d &distanceVector )
{
	const double distance = distanceVector.getLength();
	return distanceVector * getSpikyConstantGradient() * pow ( effectLength - distance, 2 ) / distance;
}

double Kernels::getViscosityKernelLaplacian(const double distance)
{
	return (effectLength - distance ) * getViscosityConstantLaplacian();
}