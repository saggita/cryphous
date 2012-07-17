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

	Kernels3D::Kernels3D(const float effectLength) :
	effectLength( effectLength )
	{
		poly6Constant = 315.0f / (64.0f * Geom::Tolerances::getPI() * pow(effectLength,9) );
		poly6ConstantGradient = 945.0f / ( 32.0f * Geom::Tolerances::getPI() * pow(effectLength,9) );
		poly6ConstantLaplacian = 945.0f / ( 32.0f * Geom::Tolerances::getPI() * pow(effectLength,9 ) );
		spikyConstantGradient = 45.0f / ( Geom::Tolerances::getPI() * pow(effectLength, 6 ) );
		viscosityConstantLaplacian = 45.0f / ( Geom::Tolerances::getPI() * pow(effectLength, 6) );
	}

	~Kernels3D(void){};

	float Kernels3D::getPoly6Kernel(const float distance)
	{
		return poly6Constant * pow( effectLength * effectLength - distance * distance, 3 );
	}

	Geom::Vector3d Kernels3D::getPoly6KernelGradient(const Geom::Vector3d& distanceVector)
	{
		const float distance = distanceVector.getLength();
		const float factor = poly6ConstantGradient * pow( effectLength * effectLength - distance * distance, 2 );
		return distanceVector * factor;
	}

	float Kernels3D::getPoly6KernelLaplacian(const float distance )
	{
		return poly6ConstantLaplacian * ( effectLength * effectLength - distance * distance ) 
			* ( 42.0f * distance * distance - 18.0f * effectLength * effectLength );
	}

	Geom::Vector3d Kernels3D::getSpikyKernelGradient(const Geom::Vector3d &distanceVector )
	{
		const float distance = distanceVector.getLength();
		return distanceVector * spikyConstantGradient * pow ( effectLength - distance, 2 ) / distance;
	}

	float Kernels3D::getViscosityKernelLaplacian(const float distance)
	{
		return (effectLength - distance ) * viscosityConstantLaplacian;
	}

protected:
	const float effectLength;
	float poly6Constant;
	float poly6ConstantGradient;
	float poly6ConstantLaplacian;
	float spikyConstantGradient;
	float viscosityConstantLaplacian;
};

	}
}

#endif