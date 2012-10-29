#ifndef __PHOTON_H__
#define __PHOTON_H__

#include "Uncopyable.h"
#include <vector>

#include "../CrystalGeom/Vector3d.h"

namespace Crystal{
	namespace Physics{
		
class Photon : private Uncopyable
{
protected:

	Photon(int id, const Geom::Vector3d& center, const Geom::Vector3d& velocity) :
		id( id), 
		center( center),
		velocity( velocity),
		absorbedTime( 0)
	{
	}

	~Photon(void){};

public:
	bool isAbsorbed() const { return absorbedTime > 0; }

public:
	Geom::Vector3d center;
	Geom::Vector3d velocity;
	const int id;
	int absorbedTime;

	friend class PhotonFactory;
};

typedef std::vector<Photon*> PhotonVector;
	
	}
}

#endif