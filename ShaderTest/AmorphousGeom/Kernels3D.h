#ifndef __KERNELS_3D_H__
#define __KERNELS_3D_H__

#include "Kernels.h"

namespace Amorphous{
	namespace Geom{

class Kernels3D : public Kernels
{
public:

	Kernels3D(const double effectLength);

	virtual ~Kernels3D(void);

protected:
	virtual void setPoly6Constant();

	virtual void setPoly6ConstantGradient();

	virtual void setPoly6ConstantLaplacian();

	virtual void setSpikyConstantGradient();

	virtual void setViscosityConstantLaplacian();
};

	}
}

#endif __KERNELS_3D_H__