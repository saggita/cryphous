#ifndef __LIGHT_SOURCE_H__
#define __LIGHT_SOURCE_H__

#include "Uncopyable.h"
#include <vector>

#include "Photon.h"
#include "PhotonFactory.h"
#include "../CrystalGeom/Vector3d.h"

namespace Crystal{
	namespace Physics{

class LightSource : private Uncopyable
{
public:
	LightSource(const int id, const Geom::Vector3d& center) :
		 id( id), center( center)
		 {
		 }

	virtual ~LightSource(void){};

public:
	/*enum Type{
		PointLight,
	};

	virtual Type getType() = 0; */

	int getID() const { return id; }

	PhotonVector getPhotons() const { return photonFactory.getPhotons(); }

	void integrateTime(const float proceedTime )
	{
		for( size_t i = 0; i < getPhotons().size(); ++i )
		{
			getPhotons()[i]->center += getPhotons()[i]->velocity * proceedTime;
		}
	}

private:
	const int id;
	const Geom::Vector3d& center;
	PhotonFactory photonFactory;
};

typedef std::vector<LightSource> LightSourceVector;

	}
}
#endif