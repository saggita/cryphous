
#include "PhysicsObjectCondition.h"

#include "../CrystalGeom/Box.h"

using namespace Crystal::Geom;
using namespace Crystal::Physics;

PhysicsObjectCondition::PhysicsObjectCondition(const Box& box, const double density, const double pressureCoefficient, const double viscosityCoefficient, const ObjectType objectType) :
box( box),
density( density),
pressureCoefficient( pressureCoefficient),
viscosityCoefficient( viscosityCoefficient),
objectType( objectType)
{
}