#ifndef __PHYSICS_OBJECT_CONDITION_H__
#define __PHYSICS_OBJECT_CONDITION_H__

#include <vector>

#include "../CrystalGeom/Box.h"

namespace Crystal{
	namespace Physics{

class PhysicsObjectCondition
{
public:
	enum ObjectType{
		Fluid,
		Rigid,
		RigidTwoWay,
	};

	enum InteractionType{
		OneWay,
		TwoWay
	};

	PhysicsObjectCondition( const std::vector<Geom::Vector3d>& points, const double density, const double pressureCoefficient, const double viscosityCoefficient, const ObjectType objectType) :
		points( points), 
			density( density),
			pressureCoefficient( pressureCoefficient),
			viscosityCoefficient( viscosityCoefficient),
			objectType( objectType)
		{
		}

	std::vector<Geom::Vector3d> getPoints() const { return points; }

	double getDensity() const { return density; }

	double getPressureCoefficient() const { return pressureCoefficient; }

	double getViscosityCoefficient() const { return viscosityCoefficient; }

	ObjectType getObjectType() const { return objectType; }

private:
	const std::vector<Geom::Vector3d> points;
	double density;
	double pressureCoefficient;
	double viscosityCoefficient;
	ObjectType objectType;
};

	}
}

#endif