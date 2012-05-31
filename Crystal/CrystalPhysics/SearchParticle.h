#pragma once

#include "../CrystalGeom/Point3d.h"

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

	SearchParticle(Particle* particle, const double effectLength): particle(particle){
		setGridID( particle->center, effectLength );
	}

	~SearchParticle(void){};

	void setGridID(const Geom::Point3d& point, const double effectLength) {
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

	std::vector<int> getNeighborIDs() const{
		std::vector<int> ids(9);
		ids[0] = getID( gridX-1, gridY-1, gridZ-1);
		ids[1] = getID( gridX-1, gridY, gridZ-1 );
		ids[2] = getID( gridX-1, gridY+1, gridZ-1);
		ids[3] = getID( gridX-1, gridY-1, gridZ );
		ids[4] = getID( gridX-1, gridY, gridZ );
		ids[5] = getID( gridX-1, gridY+1, gridZ );
		ids[6] = getID( gridX-1, gridY-1, gridZ+1 );
		ids[7] = getID( gridX-1, gridY, gridZ+1 );
		ids[8] = getID( gridX-1, gridY+1, gridZ+1);
		return ids;
	}

	Geom::Point3d getCenter() const { return particle->center; }

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

typedef std::vector< SearchParticle > SearchParticleVector;

	}
}
