
#include "PhysicsObjectCondition.h"

#include "../CrystalGeom/Box.h"

using namespace Crystal::Geom;
using namespace Crystal::Physics;

PhysicsObjectCondition::PhysicsObjectCondition(const Box& box, const double density, const double divideLength, const double pressureCoefficient, const double viscosityCoefficient, const ObjectType objectType) :
box( box),
density( density),
divideLength( divideLength),
pressureCoefficient( pressureCoefficient),
viscosityCoefficient( viscosityCoefficient),
objectType( objectType)
{
}