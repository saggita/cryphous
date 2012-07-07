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

	void enforce(PhysicsObject* rigid, const double proceedTime);

private:
	Geom::Vector3d* angleVelosity;

	void RigidEnforcer::convertToFluidForce(PhysicsObject* rigid);

	double getAngleAccelerationX( double x1,double x2,double x3, const Geom::Vector3d& I, const Geom::Vector3d& N);

	double getAngleAccelerationY( double x1,double x2,double x3, const Geom::Vector3d& I, const Geom::Vector3d& N);

	double getAngleAccelerationZ( double x1, double x2, double x3, const Geom::Vector3d& I, const Geom::Vector3d& N);

	void getAngleVelosity( const Geom::Vector3d& I, const Geom::Vector3d& N, const double proceedTime );
};

	}
}

#endif
