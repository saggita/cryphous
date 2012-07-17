#ifndef __RIGID_ENFORCER_H__
#define __RIGID_ENFORCER_H__

namespace Crystal{
	namespace Geom{
		class Vector3d;
	}
	namespace Physics{
		class PhysicsObject;

class RigidEnforcer
{
public:
	RigidEnforcer();

	~RigidEnforcer(void);

	void enforce(PhysicsObject* rigid, const float proceedTime);

private:
	Geom::Vector3d* angleVelosity;

	void RigidEnforcer::convertToFluidForce(PhysicsObject* rigid);

	float getAngleAccelerationX( float x1,float x2,float x3, const Geom::Vector3d& I, const Geom::Vector3d& N);

	float getAngleAccelerationY( float x1,float x2,float x3, const Geom::Vector3d& I, const Geom::Vector3d& N);

	float getAngleAccelerationZ( float x1, float x2, float x3, const Geom::Vector3d& I, const Geom::Vector3d& N);

	void getAngleVelosity( const Geom::Vector3d& I, const Geom::Vector3d& N, const float proceedTime );
};

	}
}

#endif
