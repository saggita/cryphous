#ifndef __KERNELS_2D_H__
#define __KERNELS_2D_H__

#include "Kernels.h"

namespace Amorphous{
	namespace Geom{

class Kernels2D : public Kernels
{
public:

	Kernels2D(const double effectLength);

	virtual ~Kernels2D(void);

protected:
	virtual void setPoly6Constant();

	virtual void setPoly6ConstantGradient();

	virtual void setPoly6ConstantLaplacian() { poly6ConstantLaplacian = 0.0; }

	virtual void setSpikyConstantGradient();

	virtual void setViscosityConstantLaplacian();
};

	}
}
#endif __KERNELS_2D_H__