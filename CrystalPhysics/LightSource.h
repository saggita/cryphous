#ifndef __LIGHT_SOURCE_H__
#define __LIGHT_SOURCE_H__

#include "Uncopyable.h"
#include <vector>

#include "Photon.h"
#include "PhotonFactory.h"
#include "../CrystalGeom/Vector3d.h"

namespace Crystal{
	namespace Physics{
		class LightSourceFactory;

class LightSource : private Uncopyable
{
protected:
	LightSource() :
		id(-1),
		center( Geom::Vector3d( 0.0f, 0.0f, 0.0f) )
	{
	}

	void addPhotons(const size_t howMany);

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

	void integrateTime(const float proceedTime );


private:
	const int id;
	const Geom::Vector3d center;
	PhotonFactory photonFactory;

	friend LightSourceFactory;
};

typedef std::vector<LightSource*> LightSourceVector;

	}
}
#endif