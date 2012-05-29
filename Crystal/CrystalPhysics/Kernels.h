#pragma once

namespace Crystal{
	namespace Geom{
		class Vector3d;
	}

	namespace Physics{

class Kernels
{
public:
	Kernels(const double effectLength);

	double getPoly6Kernel( const double distance);

	Geom::Vector3d getPoly6KernelGradient( const Geom::Vector3d& distanceVector );

	double getPoly6KernelLaplacian( const double distance );

	Geom::Vector3d getSpikyKernelGradient( const Geom::Vector3d& distanceVector );

	double getViscosityKernelLaplacian( const double distance );

protected:
	double getPoly6Constant() const { return poly6Constant; }

	double getPoly6ConstantGradient() const { return poly6ConstantGradient; }

	double getPoly6ConstantLaplacian() const { return poly6ConstantLaplacian; }

	double getSpikyConstantGradient() const { return spikyConstantGradient; }

	double getViscosityConstantLaplacian() const { return viscosityConstantLaplacian; }

	virtual void setPoly6Constant() = 0;

	virtual void setPoly6ConstantGradient() = 0;

	virtual void setPoly6ConstantLaplacian() = 0;

	virtual void setSpikyConstantGradient() = 0;

	virtual void setViscosityConstantLaplacian() = 0;

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