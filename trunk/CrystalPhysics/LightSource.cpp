#include "LightSource.h"

#include <random>

using namespace Crystal::Physics;

#ifdef _OPENMP
#include <omp.h>
#endif

void LightSource::integrateTime(const float proceedTime)
{
	std::tr1::random_device rand;
	if( getPhotons().size() < 500000 ) {
		std::vector<Geom::Vector3d> points;
		std::vector<Geom::Vector3d> velocities;
		
		for( int i = 0; i < 100; ++i ) {
			points.push_back( center );
			velocities.push_back( Geom::Vector3d( rand(), rand(), rand() ) );
			velocities.back().normalize();
			velocities.back() *= 10.0;
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