#ifndef __ABSORBED_PHOTON__
#define __ABSORBED_PHOTON__

#include "../CrystalGeom/Vector3d.h"

namespace Crystal{
	namespace Physics{

class AbsorbedPhoton
{
public:
	AbsorbedPhoton(const Geom::Vector3d& center) :
		center( center),
		lifeTime(1)
	{
	}

	~AbsorbedPhoton(void)
	{
	}

private:
	const Geom::Vector3d center;
	int lifeTime;
};

	}
}

#endif