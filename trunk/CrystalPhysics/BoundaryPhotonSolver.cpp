#include "BoundaryPhotonSolver.h"

#include "LightSource.h"

using namespace Crystal::Geom;
using namespace Crystal::Physics;

#ifdef _OPENMP
#include <omp.h>
#endif

void BoundaryPhotonSolver::reflectPhoton(const Box& box)
{
	const PhotonVector& photons = lightSource->getPhotons();
	#pragma omp parallel for
	for( int i = 0; i < static_cast<int>(photons.size()); ++i ) {
		Photon* photon = photons[i];
		int random = std::rand() % 10000;
		bool doStop = random > 5000;
		if( photon->center.getX() > box.getMaxX() ) {
			doStop ? photon->velocity.setZero() : photon->velocity.setX( -::fabs(photon->velocity.getX()) );
		}
		else if( photon->center.getX() < box.getMinX() ) {
			doStop ? photon->velocity.setZero() : photon->velocity.setX( ::fabs(photon->velocity.getX()) );
		}

		if( photon->center.getY() > box.getMaxY() ) {
			doStop ? photon->velocity.setZero() : photon->velocity.setY( -::fabs(photon->velocity.getY()) );
		}
		else if( photon->center.getY() < box.getMinY() ) {
			doStop ? photon->velocity.setZero() : photon->velocity.setY( ::fabs(photon->velocity.getY()) );
		}

		if( photon->center.getZ() > box.getMaxZ() ) {
			doStop ? photon->velocity.setZero() : photon->velocity.setZ( -::fabs(photon->velocity.getZ()) );
		}
		else if( photon->center.getZ() < box.getMinZ() ) {
			doStop ? photon->velocity.setZero() : photon->velocity.setZ( ::fabs(photon->velocity.getZ()) );
		}
	}
}