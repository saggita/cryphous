#ifndef __KERNELS_3D_H__
#define __KERNELS_3D_H__

#include "../CrystalGeom/Vector3d.h"
#include "../CrystalGeom/Tolerances.h"
#include <cmath>

namespace Crystal{
	namespace Physics{

class Kernels3D
{
public:

	Kernels3D::Kernels3D(const double effectLength) :
	effectLength( effectLength )
	{
		poly6Constant = 315.0 / (64.0 * Geom::Tolerances::getPI() * pow(effectLength,9) );
		poly6ConstantGradient = 945.0 / ( 32.0 * Geom::Tolerances::getPI() * pow(effectLength,9) );
		poly6ConstantLaplacian = 945.0 / ( 32 * Geom::Tolerances::getPI() * pow(effectLength,9 ) );
		spikyConstantGradient = 45.0 / ( Geom::Tolerances::getPI() * pow(effectLength, 6 ) );
		viscosityConstantLaplacian = 45.0 / ( Geom::Tolerances::getPI() * pow(effectLength, 6) );
	}

	~Kernels3D(void){};

	double Kernels3D::getPoly6Kernel(const double distance)
	{
		return poly6Constant * pow( effectLength * effectLength - distance * distance, 3 );
	}

	Geom::Vector3d Kernels3D::getPoly6KernelGradient(const Geom::Vector3d& distanceVector)
	{
		const double distance = distanceVector.getLength();
		const double factor = poly6ConstantGradient * pow( effectLength * effectLength - distance * distance, 2 );
		return distanceVector * factor;
	}

	double Kernels3D::getPoly6KernelLaplacian(const double distance )
	{
		return poly6ConstantLaplacian * ( effectLength * effectLength - distance * distance ) 
			* ( 42.0 * distance * distance - 18.0 * effectLength * effectLength );
	}

	Geom::Vector3d Kernels3D::getSpikyKernelGradient(const Geom::Vector3d &distanceVector )
	{
		const double distance = distanceVector.getLength();
		return distanceVector * spikyConstantGradient * pow ( effectLength - distance, 2 ) / distance;
	}

	double Kernels3D::getViscosityKernelLaplacian(const double distance)
	{
		return (effectLength - distance ) * viscosityConstantLaplacian;
	}

protected:
	const double effectLength;
	double poly6Constant;
	double poly6ConstantGradient;
	double poly6ConstantLaplacian;
	double spikyConstantGradient;
	double viscosityConstantLaplacian;
};

	}
}

#endif