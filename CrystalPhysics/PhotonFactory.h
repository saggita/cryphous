#ifndef __PHOTON_FACTORY_H__
#define __PHOTON_FACTORY_H__

#include <vector>
#include "Uncopyable.h"

#include "Photon.h"
#include "../CrystalGeom/Vector3d.h"


namespace Crystal{
	namespace Physics{
		
class PhotonFactory : private Uncopyable
{
public:
	PhotonFactory(void):
	nextID(0)
	{}

	~PhotonFactory(void)
	{
		for( size_t i = 0; i < photons.size(); ++i ) {
			delete photons[i];
		}
	}

	PhotonVector addPhotons(const std::vector<Geom::Vector3d>& points, const std::vector<Geom::Vector3d>& velocities)
	{
		for( size_t i = 0; i < points.size(); ++i ) {
			photons.push_back( new Photon( nextID++, points[i], velocities[i] ) );
		}
		return photons;
	}

	PhotonVector getPhotons() const { return photons; }

private:
	int nextID;
	PhotonVector photons;
};

	}
}

#endif