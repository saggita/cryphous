#ifndef __SEARCH_PARTICLE_H__
#define __SEARCH_PARTICLE_H__

#include "../CrystalGeom/Vector3d.h"

#include "Particle.h"

#include "SearchParticle.h"
#include "SimulationSetting.h"

#include <vector>

namespace Crystal{
	namespace Physics{
		class Particle;
		class SearchParticleFactory;

class SearchParticle
{
public:

	SearchParticle(){};

	SearchParticle(const int gridID) : gridID( gridID)
	{
	}

	SearchParticle(Particle* particle, const double effectLength): particle(particle){
		setGridID( particle->center, effectLength );
	}

	~SearchParticle(void){};

	void setGridID(const Geom::Vector3d& point, const double effectLength) {
		gridX = static_cast<int>( point.getX() / effectLength );
		gridY = static_cast<int>( point.getY() / effectLength );
		gridZ = static_cast<int>( point.getZ() / effectLength );

		gridID = getID( gridX, gridY, gridZ );
	}

	bool operator<(const SearchParticle& rhs) const {
		return this->gridID < rhs.gridID;
	}

	bool operator==(const SearchParticle& rhs) const {
		return this->gridID == rhs.gridID;
	}

	Particle* getParticle() const { return particle; }

	int getGridID() const { return gridID; }

	std::vector<int> getForwardIDs() const{
		std::vector<int> ids(4);
		ids[0] = getID( gridX-1, gridY+1, gridZ );
		ids[1] = getID( gridX-1, gridY-1, gridZ+1 );
		ids[2] = getID( gridX-1, gridY, gridZ+1 );
		ids[3] = getID( gridX-1, gridY+1, gridZ+1);
		return ids;
	}

	Geom::Vector3d getCenter() const { return particle->center; }

private:
	Particle* particle;
	int gridID;

	int gridX;
	int gridY;
	int gridZ;

	int getID( int idX, int idY, int idZ ) const{
		return (idZ << 20) + (idY << 10) + idX;
	}
};

static bool operator<(SearchParticle& lhs, int gridID)
{
	return lhs.getGridID() < gridID;
}

static bool operator<(const int gridID, SearchParticle& rhs)
{
	return gridID < rhs.getGridID();
}

static bool operator<(const int gridID, const SearchParticle& rhs)
{
	return gridID < rhs.getGridID();
}

typedef std::vector< SearchParticle > SearchParticleVector;

	}
}

#endif