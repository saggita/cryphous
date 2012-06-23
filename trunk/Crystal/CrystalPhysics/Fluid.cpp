#include "Fluid.h"

#include "Particle.h"

#include "../CrystalGeom/Vector3d.h"
#include "../CrystalGeom/Vector3d.h"

#include "PhysicalTimeIntegrator.h"
#include "EnforcerBase.h"

#include <boost/foreach.hpp>

using namespace Crystal::Geom;
using namespace Crystal::Physics;


Fluid::Fluid(const int id, const double density, const double gasConstant, const double viscosityCoefficient, ParticleFactory* particleFactory) :
PhysicsObject( id, density, gasConstant, viscosityCoefficient,particleFactory, new PhysicalTimeIntegrator(), new EnforcerBase() )
{
}

Fluid::~Fluid(void)
{
}