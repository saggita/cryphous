#ifndef __PHYSICS_OBJECT_CONDITION_H__
#define __PHYSICS_OBJECT_CONDITION_H__

#include <boost/noncopyable.hpp>
#include <list>

#include "../CrystalGeom/Box.h"

namespace Crystal{
	namespace Physics{

class PhysicsObjectCondition : public boost::noncopyable
{
public:
	enum ObjectType{
		Fluid,
		Rigid,
		RigidTwoWay,
		Cloth
	};

	enum InteractionType{
		OneWay,
		TwoWay
	};

	PhysicsObjectCondition( const Geom::Box& box, const double density, const double divideLenth, const double pressureCoefficient, const double viscosityCoefficient, const ObjectType objectType);

	const Geom::Box& getBox() const { return box; }

	double getDensity() const { return density; }

	double getDivideLength() const { return divideLength; }

	double getPressureCoefficient() const { return pressureCoefficient; }

	double getViscosityCoefficient() const { return viscosityCoefficient; }

	ObjectType getObjectType() const { return objectType; }

	void setDensity(const double density) { this->density = density; }

	void setPressureCoefficient(const double pressureCoefficient) { this->pressureCoefficient = pressureCoefficient; }

	void setViscosityCoefficient(const double viscosityCoefficient) { this->viscosityCoefficient = viscosityCoefficient; }

	InteractionType getChemicalInteractionType() const { return chemicalInteraction; }

private:
	const Geom::Box box;
	double density;
	double divideLength;
	double pressureCoefficient;
	double viscosityCoefficient;
	ObjectType objectType;
	InteractionType chemicalInteraction;
};

typedef std::list<PhysicsObjectCondition*> PhysicsObjectConditionList;
	}
}

#endif