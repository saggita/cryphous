#ifndef __BOUNDARY_PHOTON_SOLVER_H__
#define __BOUNDARY_PHOTON_SOLVER_H__

#include "../CrystalGeom/Vector3d.h"
#include "../CrystalGeom/Box.h"

#include <vector>

namespace Crystal{
	namespace Physics{
		class LightSource;

class BoundaryPhotonSolver
{
public:

	BoundaryPhotonSolver(LightSource* lightSource)
		: lightSource( lightSource)
	{}

	~BoundaryPhotonSolver(void){};

	void reflectPhoton(const Geom::Box& box);
	
private:
	LightSource* lightSource;
};

	}
}

#endif