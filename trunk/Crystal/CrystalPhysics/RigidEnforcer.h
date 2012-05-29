#ifndef __RIGID_ENFORCER_H__
#define __RIGID_ENFORCER_H__

#include "EnforcerBase.h"

namespace Crystal{
	namespace Geom{
		class Vector3d;
	}
	namespace Physics{
		class RigidTwoWay;

class RigidEnforcer : public EnforcerBase
{
public:
	RigidEnforcer();

	~RigidEnforcer(void);

	virtual void enforce(PhysicsObject* rigid, const double proceedTime);

private:
	Geom::Vector3d* angleVelosity;

	void RigidEnforcer::convertToFluidForce(PhysicsObject* rigid);

	//void convertToFluidForce();

	//Geom::Vector3d RigidEnforcer::getForce() const;

	double getAngleAccelerationX( double x1,double x2,double x3, const Geom::Vector3d& I, const Geom::Vector3d& N);

	double getAngleAccelerationY( double x1,double x2,double x3, const Geom::Vector3d& I, const Geom::Vector3d& N);

	double getAngleAccelerationZ( double x1, double x2, double x3, const Geom::Vector3d& I, const Geom::Vector3d& N);

	void getAngleVelosity( const Geom::Vector3d& I, const Geom::Vector3d& N, const double proceedTime );
};

	}
}

#endif
