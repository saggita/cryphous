#ifndef __RIGID_ENFORCER_H__
#define __RIGID_ENFORCER_H__

#include "../CryphousGeometry/Tolerances.h"
#include "../CryphousGeometry/Vector3d.h"
#include "../CryphousGeometry/Quaternion.h"
#include "../CryphousGeometry/Matrix3d.h"
#include "PhysicsObject.h"
#include "Particle.h"

namespace Cryphous{
	namespace Physics{

class RigidEnforcer
{
public:
	RigidEnforcer(){};

	~RigidEnforcer(void){};

	void enforce(PhysicsObject* rigid, const float proceedTime)
	{
		const Geometry::Vector3d& objectCenter = rigid->getCenter();
		const Geometry::Vector3d& velocityAverage = rigid->getAverageVelosity();

		const ParticleVector& particles = rigid->getParticles();
		for( ParticleVector::const_iterator iter = particles.begin(); iter != particles.end(); ++iter ) {
			(*iter)->velocity = velocityAverage;
		}

		for( ParticleVector::const_iterator iter = particles.begin(); iter != particles.end(); ++iter ) {
			(*iter)->center -= objectCenter;
		}
		assert( rigid->getCenter() == Geometry::Vector3d( 0.0, 0.0, 0.0 ) );

		Geometry::Vector3d inertiaMoment( 0.0, 0.0, 0.0 );
		Geometry::Vector3d torque( 0.0, 0.0, 0.0 );
	
		for( ParticleVector::const_iterator iter = particles.begin(); iter != particles.end(); ++iter ) {
			Particle* particle = (*iter);
			const Geometry::Vector3d& center = particle->center;
		
			Geometry::Vector3d particleMoment( pow( center.y, 2) + pow( center.z, 2),
				pow( center.z, 2 ) + pow( center.x, 2),
				pow( center.x, 2 ) + pow( center.y, 2) );
			inertiaMoment += (particleMoment) * particle->getMass();

			const Geometry::Vector3d diffVector( Geometry::Vector3d( 0.0, 0.0, 0.0), particle->center );
			const Geometry::Vector3d& particleTorque = diffVector.getOuterProduct( particle->force * particle->getVolume() );
			torque += particleTorque;
		}

		getAngleVelosity( inertiaMoment , torque, proceedTime );

		if( Geometry::Tolerances::isEqualStrictly( angleVelosity.getLength() ) ) {
			for( ParticleVector::const_iterator iter = particles.begin(); iter != particles.end(); ++iter ) {
				(*iter)->center += objectCenter;
			}
			convertToFluidForce( rigid);
			return;
		}
		const float rotateAngle = angleVelosity.getLength() * proceedTime;
		if( rotateAngle < 1.0e-5 ) {
			for( ParticleVector::const_iterator iter = particles.begin(); iter != particles.end(); ++iter ) {
				(*iter)->center += objectCenter;
			}
			convertToFluidForce( rigid);
			return;
		}

		Geometry::Quaternion quaternion( angleVelosity.getNormalized(), rotateAngle );
		const Geometry::Matrix3d& rotateMatrix = quaternion.getMatrix();
		for( ParticleVector::const_iterator iter = particles.begin(); iter != particles.end(); ++iter ) {
			(*iter)->center.rotate( rotateMatrix );
		}

		for( ParticleVector::const_iterator iter = particles.begin(); iter != particles.end(); ++iter ) {
			(*iter)->center += objectCenter;
		}
		convertToFluidForce( rigid);
	}

private:
	Geometry::Vector3d angleVelosity;

	void RigidEnforcer::convertToFluidForce(PhysicsObject* rigid)
	{	
		Geometry::Vector3d totalForce( 0.0, 0.0, 0.0 );
		const ParticleVector& particles = rigid->getParticles();
		for( ParticleVector::const_iterator iter = particles.begin(); iter != particles.end(); ++iter ) {
			totalForce += (*iter)->force * (*iter)->getVolume();
		}

		const float weight =  rigid->getWeight();
		for( ParticleVector::const_iterator iter = particles.begin(); iter != particles.end(); ++iter ) {
			(*iter)->force = totalForce / weight * (*iter)->density;
		}
	}

	float getAngleAccelerationX( float x1,float x2,float x3, const Geometry::Vector3d& I, const Geometry::Vector3d& N)
	{
		return (N.x + ( I.y - I.z) * x2 * x3 ) / I.x - 10.0f * x1;
	}

	float getAngleAccelerationY( float x1,float x2,float x3, const Geometry::Vector3d& I, const Geometry::Vector3d& N)
	{
		return (N.y + ( I.z - I.x) * x3 * x1 ) / I.y - 10.0f * x2;
	}

	float getAngleAccelerationZ( float x1, float x2, float x3, const Geometry::Vector3d& I, const Geometry::Vector3d& N)
	{
		return (N.z + ( I.x - I.y ) * x1 * x2 ) / I.z - 10.0f * x3;
	}

	void getAngleVelosity( const Geometry::Vector3d& I, const Geometry::Vector3d& N, const float proceedTime )
	{
		float x1,x2,x3;
		const int innerSteps = 10;
		float h = proceedTime / innerSteps;
	
		x1 = angleVelosity.x;
		x2 = angleVelosity.y;
		x3 = angleVelosity.z;

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

		angleVelosity.x = x1;
		angleVelosity.y = x2;
		angleVelosity.z = x3;
	}
};

	}
}

#endif
