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

	SearchParticle(Particle* particle, const float effectLength): particle(particle){
		setGridID( particle->center, effectLength );
	}

	~SearchParticle(void){};

	void setGridID(const Geom::Vector3d& point, const float effectLength) {
		int gridX = static_cast<int>( point.x / effectLength );
		int gridY = static_cast<int>( point.y / effectLength );
		int gridZ = static_cast<int>( point.z / effectLength );
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

	Geom::Vector3d getCenter() const { return particle->center; }

private:
	Particle* particle;
	int gridID;

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