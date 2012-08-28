#ifndef __RIGID_ENFORCER_H__
#define __RIGID_ENFORCER_H__

#include "../CrystalGeom/Tolerances.h"
#include "../CrystalGeom/Vector3d.h"
#include "../CrystalGeom/Quaternion.h"
#include "../CrystalGeom/Matrix3d.h"
#include "PhysicsObject.h"
#include "Particle.h"

#include <boost/foreach.hpp>

namespace Crystal{
	namespace Physics{

class RigidEnforcer
{
public:
	RigidEnforcer(){};

	~RigidEnforcer(void){};

	void enforce(PhysicsObject* rigid, const float proceedTime)
	{
		const Geom::Vector3d& objectCenter = rigid->getCenter();
		const Geom::Vector3d& velocityAverage = rigid->getAverageVelosity();

		BOOST_FOREACH( Particle* particle, rigid->getParticles() ) {
			particle->velocity = velocityAverage;
		}

		BOOST_FOREACH( Particle* particle, rigid->getParticles() ) {
			particle->center -= objectCenter;
		}
		assert( rigid->getCenter() == Geom::Vector3d( 0.0, 0.0, 0.0 ) );

		Geom::Vector3d inertiaMoment( 0.0, 0.0, 0.0 );
		Geom::Vector3d torque( 0.0, 0.0, 0.0 );
	
		BOOST_FOREACH( Particle* particle, rigid->getParticles() ) {
			const Geom::Vector3d& center = particle->center;
		
			Geom::Vector3d particleMoment( pow( center.getY(), 2) + pow( center.getZ(), 2),
				pow( center.getZ(), 2 ) + pow( center.getX(), 2),
				pow( center.getX(), 2 ) + pow( center.getY(), 2) );
			inertiaMoment += (particleMoment) * particle->getMass();

			const Geom::Vector3d diffVector( Geom::Vector3d( 0.0, 0.0, 0.0), particle->center );
			const Geom::Vector3d& particleTorque = diffVector.getOuterProduct( particle->force * particle->getVolume() );
			torque += particleTorque;
		}

		getAngleVelosity( inertiaMoment , torque, proceedTime );

		if( Geom::Tolerances::isEqualAsDenominator( angleVelosity.getLength() ) ) {
			BOOST_FOREACH( Particle* particle, rigid->getParticles() ) {
				particle->center += objectCenter;
			}
			convertToFluidForce( rigid);
			return;
		}
		const float rotateAngle = angleVelosity.getLength() * proceedTime;
		if( rotateAngle < 1.0e-5 ) {
			BOOST_FOREACH( Particle* particle, rigid->getParticles() ) {
				particle->center += objectCenter;
			}
			convertToFluidForce( rigid);
			return;
		}

		Geom::Quaternion quaternion( angleVelosity.getNormalized(), rotateAngle );
		const Geom::Matrix3d& rotateMatrix = quaternion.getMatrix();
		BOOST_FOREACH( Particle* particle, rigid->getParticles() ) {
			particle->center.rotate( rotateMatrix );
		}

		BOOST_FOREACH( Particle* particle, rigid->getParticles() ) {
			particle->center += objectCenter;
		}
		convertToFluidForce( rigid);
	}

private:
	Geom::Vector3d angleVelosity;

	void RigidEnforcer::convertToFluidForce(PhysicsObject* rigid)
	{	
		Geom::Vector3d totalForce( 0.0, 0.0, 0.0 );
		BOOST_FOREACH( Particle* particle, rigid->getParticles() ) {
			totalForce += particle->force * particle->getVolume();
		}

		const float weight =  rigid->getWeight();
		BOOST_FOREACH( Particle* particle, rigid->getParticles() ) {
			particle->force = totalForce / weight * particle->density;
		}
	}

	float getAngleAccelerationX( float x1,float x2,float x3, const Geom::Vector3d& I, const Geom::Vector3d& N)
	{
		return (N.getX() + ( I.getY() - I.getZ()) * x2 * x3 ) / I.getX() - 10.0f * x1;
	}

	float getAngleAccelerationY( float x1,float x2,float x3, const Geom::Vector3d& I, const Geom::Vector3d& N)
	{
		return (N.getY() + ( I.getZ() - I.getX()) * x3 * x1 ) / I.getY() - 10.0f * x2;
	}

	float getAngleAccelerationZ( float x1, float x2, float x3, const Geom::Vector3d& I, const Geom::Vector3d& N)
	{
		return (N.getZ() + ( I.getX() - I.getY() ) * x1 * x2 ) / I.getZ() - 10.0f * x3;
	}

	void getAngleVelosity( const Geom::Vector3d& I, const Geom::Vector3d& N, const float proceedTime )
	{
		float x1,x2,x3;
		const int innerSteps = 10;
		float h = proceedTime / innerSteps;
	
		x1 = angleVelosity.getX();
		x2 = angleVelosity.getY();
		x3 = angleVelosity.getZ();

		for( int i = 0; i < innerSteps; i++ ){
			const float k11 = h * getAngleAccelerationX( x1,x2,x3,I,N);
			const float k21 = h * getAngleAccelerationY( x1,x2,x3,I,N);
			const float k31 = h * getAngleAccelerationZ( x1,x2,x3,I,N);
			const float k12 = h * getAngleAccelerationX( x1 + k11 / 2.0f, x2 + k21 / 2.0f, x3 + k31 / 2.0f,I,N);
			const float k22 = h * getAngleAccelerationY( x1 + k11 / 2.0f, x2 + k21 / 2.0f, x3 + k31 / 2.0f,I,N);
			const float k32 = h * getAngleAccelerationZ( x1 + k11 / 2.0f, x2 + k21 / 2.0f, x3 + k31 / 2.0f,I,N);
			const float k13 = h * getAngleAccelerationX( x1 + k12 / 2.0f, x2 + k22 / 2.0f, x3 + k32 / 2.0f,I,N);
			const float k23 = h * getAngleAccelerationY( x1 + k12 / 2.0f, x2 + k22 / 2.0f, x3 + k32 / 2.0f,I,N);
			const float k33 = h * getAngleAccelerationZ( x1 + k12 / 2.0f, x2 + k22 / 2.0f, x3 + k32 / 2.0f,I,N);
			const float k14 = h * getAngleAccelerationX( x1 + k13, x2 + k23, x3 + k33,I,N);
			const float k24 = h * getAngleAccelerationY( x1 + k13, x2 + k23, x3 + k33,I,N);
			const float k34 = h * getAngleAccelerationZ( x1 + k13, x2 + k23, x3 + k33,I,N);

			const float dx1 = (k11 + 2.0f * k12 + 2.0f * k13 + k14) / 6.0f;
			const float dx2 = (k21 + 2.0f * k22 + 2.0f * k23 + k24) / 6.0f;
			const float dx3 = (k31 + 2.0f * k32 + 2.0f * k33 + k34) / 6.0f;

			x1 += dx1;
			x2 += dx2;
			x3 += dx3;
		}

		angleVelosity.setX( x1 );
		angleVelosity.setY( x2 );
		angleVelosity.setZ( x3 );
	}
};

	}
}

#endif