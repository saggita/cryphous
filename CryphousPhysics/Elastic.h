#ifndef __CRYPHOUS_ELASTIC_H__
#define __CRYPHOUS_ELASTIC_H__

#include "../CryphousGeometry/Vector3d.h"

#include "PhysicsObject.h"
#include "Particle.h"
#include "SimulationSetting.h"

namespace Cryphous{
	namespace Physics{

class Elastic : public PhysicsObject
{
public:
	Elastic(const int id, const float density, const float gasConstant, const float viscosityCoefficient,ParticleFactory* particleFactory) :
	  PhysicsObject( id, density, gasConstant, viscosityCoefficient,particleFactory )
	  {
	  }

	virtual ~Elastic(void){};

	virtual Type getType() { return PhysicsObject::Elastic; }

	virtual void integrateTime(const float proceedTime);

	virtual void enforce(const float proceedTime);
};
	}
}

#endif