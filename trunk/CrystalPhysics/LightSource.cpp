#include "LightSource.h"

using namespace Crystal::Physics;

#ifdef _OPENMP
#include <omp.h>
#endif

void LightSource::integrateTime(const float proceedTime )
	{
		if( getPhotons().size() < 500000 ) {
			std::vector<Geom::Vector3d> points;
			std::vector<Geom::Vector3d> velocities;
			
			for( int i = 0; i < 10; ++i ) {
				points.push_back( Geom::Vector3d( center.getX(), center.getY(), center.getZ() ) );
				velocities.push_back( Geom::Vector3d( (rand() % 1000) / 1000.0f, (rand() % 1000) / 1000.0f, (rand() % 1000) / 1000.0f ) );
			}
			photonFactory.addPhotons( points, velocities );
		}
		const PhotonVector& photons = getPhotons();
		
		#pragma omp parallel for
		for( int i = 0; i < static_cast<int>( photons.size() ); ++i )
		{
			photons[i]->center += photons[i]->velocity * proceedTime;
		}
	}