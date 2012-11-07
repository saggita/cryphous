#include "LightSource.h"

#include <random>

using namespace Crystal::Physics;

#ifdef _OPENMP
#include <omp.h>
#endif

void LightSource::addPhotons(const size_t howMany)
{
	std::vector<Geom::Vector3d> points;
	std::vector<Geom::Vector3d> velocities;

	for( size_t j = 0; j < howMany; ++j ) {	
		points.push_back( center );
		velocities.push_back( Geom::Vector3d( rand(), -1.0 * rand(), rand() ) );
		velocities.back().normalize();
		velocities.back() *= (rand() % 100) / 100.0 * velocity;
	}

	photonFactory.addPhotons( points, velocities );
}

void LightSource::integrateTime(const float proceedTime)
{	
	const PhotonVector& photons = getPhotons();

	#pragma omp parallel for
	for( int i = 0; i < static_cast<int>( photons.size() ); ++i )
	{
		if( !photons[i]->isAbsorbed() ) {
			photons[i]->center += photons[i]->velocity * proceedTime;
		}
		else {
			++(photons[i]->absorbedTime);
		}
	}
}

void LightSource::initAbsorbedPhotons()
{
	const PhotonVector& photons = getPhotons();
	#pragma omp parallel for
	for( int i = 0; i < static_cast<int>( photons.size() ); ++i ) {
		if( photons[i]->absorbedTime > 20 ) {
			photons[i]->center = this->getCenter();
			photons[i]->velocity = Geom::Vector3d( rand(), -1.0f * rand(), rand() );
			photons[i]->velocity.normalize();
			photons[i]->velocity *= (rand() % 100) / 100.0 * velocity;
			photons[i]->absorbedTime = 0;
		}
	}
}