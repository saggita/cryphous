#ifndef __SEARCH_PHOTON_H__
#define __SEARCH_PHOTON_H__

#include "../CrystalGeom/Vector3d.h"

#include "Photon.h"

#include "SimulationSetting.h"

#include <vector>

namespace Crystal{
	namespace Physics{
		class Photon;
		class SearchPhotonFactory;

class SearchPhoton
{
public:

	SearchPhoton(){};

	SearchPhoton(const int gridID) : gridID( gridID)
	{
	}

	SearchPhoton(Photon* photon, const float effectLength): photon(photon){
		setGridID( photon->center, effectLength );
	}

	~SearchPhoton(void){};

	void setGridID(const Geom::Vector3d& point, const float effectLength) {
		int gridX = static_cast<int>( point.getX() / effectLength );
		int gridY = static_cast<int>( point.getY() / effectLength );
		int gridZ = static_cast<int>( point.getZ() / effectLength );
		gridID = getID( gridX, gridY, gridZ );
	}

	bool operator<(const SearchPhoton& rhs) const {
		return this->gridID < rhs.gridID;
	}

	bool operator==(const SearchPhoton& rhs) const {
		return this->gridID == rhs.gridID;
	}

	Photon* getPhoton() const { return photon; }

	int getGridID() const { return gridID; }

	Geom::Vector3d getCenter() const { return photon->center; }

private:
	Photon* photon;
	int gridID;

	int getID( int idX, int idY, int idZ ) const{
		return (idZ << 20) + (idY << 10) + idX;
	}
};

static bool operator<(SearchPhoton& lhs, int gridID)
{
	return lhs.getGridID() < gridID;
}

static bool operator<(const int gridID, SearchPhoton& rhs)
{
	return gridID < rhs.getGridID();
}

static bool operator<(const int gridID, const SearchPhoton& rhs)
{
	return gridID < rhs.getGridID();
}

typedef std::vector< SearchPhoton > SearchPhotonVector;

	}
}

#endif