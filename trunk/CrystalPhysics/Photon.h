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
		absorbed( false)
	{
	}

	~Photon(void){};

	bool isAbsorbed() const { return absorbed; }

public:
	Geom::Vector3d center;
	Geom::Vector3d velocity;
	const int id;
	bool absorbed;


	friend class PhotonFactory;
};

typedef std::vector<Photon*> PhotonVector;
	
	}
}

#endif