#include "BoundaryCoordinator.h"

#include "../Math/Box.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

#ifdef _OPENMP
#include <omp.h>
#endif

float getForce(const float over, const float timeStep)
{
	return -over / timeStep / timeStep; 
}

Vector3d getForceX(const float x, const Box& box, const float timeStep)
{
	float over = 0.0f;
	if( x > box.maxX ) {
		over = x - box.maxX;
	}
	else if( x < box.minX ) {
		over = x - box.minX;
	}

	const float force = getForce( over, timeStep ); 
	return Vector3d::UnitX() * force;
}

Vector3d getForceY(const float y, const Box& box, const float timeStep)
{
	float over = 0.0f;
	if( y > box.maxY ) {
		over = y - box.maxY;
	}
	else if( y < box.minY ) {
		over = y - box.minY;
	}
	const float force = getForce( over, timeStep );
	return Vector3d::UnitY() * force;
}

Vector3d getForceZ(const float z, const Box& box, const float timeStep)
{
	float over = 0.0f;
	if( z > box.maxZ ) {
		over = z - box.maxZ;
	}
	else if( z < box.minZ ) {
		over = z - box.minZ;
	}
	const float force = getForce( over, timeStep );
	return Vector3d::UnitZ() * force;
}

Vector3d getForce( const Vector3d& center, const float timeStep, const Box& box)
{
	Vector3d force = Vector3d::Zero();

	force += getForceX( center.x, box, timeStep );
	force += getForceY( center.y, box, timeStep );
	force += getForceZ( center.z, box, timeStep );

	return force;
}

void BoundaryCoordinator::coordinate(const ParticleVector& particles, const float timeStep)
{
	#pragma omp parallel for
	for( int i = 0; i < static_cast<int>( particles.size() ); ++i ) {
		particles[i]->addForce( ::getForce( particles[i]->getCenter(), timeStep, box ) * particles[i]->getDensity() );
	}
};

Vector3d getForce( const Vector3d& pos, const float timeStep, const float radius, const Vector3d& center )
{
	if( pos.getDistanceSquared( center ) > radius * radius ) {
		Vector3d normal = pos - center;
		const float over = pos.getDistance( center ) - radius;
		normal.normalize();
		return normal * ::getForce( over, timeStep );
	}
	return Vector3d::Zero();
}

Vector3d getPosition( const Vector3d& pos, const float radius, const Vector3d& center)
{
	if( pos.getDistanceSquared( center ) > radius * radius ) {
		Vector3d normal = pos - center;
		normal.normalize();
		return normal * radius;
	}
	return pos;
}

void SphereBoundaryCoordinator::coordinate( const ParticleVector& particles, const float timeStep )
{
	#pragma omp parallel for
	for( int i = 0; i < static_cast<int>( particles.size() ); ++i ) {
		particles[i]->addForce( ::getForce( particles[i]->getCenter(), timeStep, radius, center ) );
		//particles[i]->setCenter( ::getPosition( particles[i]->getCenter(), radius, center ) );
	}
}