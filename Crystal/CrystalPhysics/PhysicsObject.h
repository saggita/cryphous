#pragma once

#include <boost/noncopyable.hpp>
#include <list>

#include "ParticleFactory.h"
#include "SpringParticleFactory.h"

namespace Crystal{

	namespace Geom{
		class Vector3d;
		class Point3d;
	}

	namespace Physics{
		class Particle;
		typedef std::vector<Particle*> ParticleVector;
		class PhysicsObjectFactory;
		class SpringParticle;
		typedef std::list<SpringParticle*> SpringParticleList;
		class PhysicalTimeIntegratorBase;
		class EnforcerBase;


class PhysicsObject : private boost::noncopyable
{
protected:
	PhysicsObject(const int id, const double density, const double gasConstant, const double viscosityCoefficient, ParticleFactory* particleFactory,
		PhysicalTimeIntegratorBase* physicalTimeIntegratorBase,
		EnforcerBase* enforcerBase);

	virtual ~PhysicsObject(void);

public:
	enum Type{
		Fluid,
		Rigid,
		RigidTwoWay,
		Air,
		Cloth
	};

	virtual Type getType() = 0;

	int getID() const { return id; }

	ParticleVector getParticles() const { return particleFactory->getParticles(); }

	virtual void enforce(const double proceedTime);

	void integrateTime(const double proceedTime );

	Geom::Point3d getCenter() const;

	Geom::Vector3d getAverageVelosity() const;

	double getWeight() const;

	double getDensity() const {return density; }

	double getGasConstant() const { return gasConstant; }

	double getViscosityCoefficient() const { return viscosityCoefficient; }

	ParticleFactory* getParticleFactory() const { return particleFactory; }

	//virtual SpringParticleList getSpringParticles() const { return SpringParticleList(); }

	virtual ParticleGrid getParticleGrid() const { return ParticleGrid(); }

private:
	const int id;
	const double density;
	const double gasConstant;
	const double viscosityCoefficient;
	ParticleFactory* particleFactory;

protected:
	PhysicalTimeIntegratorBase* physicalTimeIntegratorBase;
	EnforcerBase* enforcerBase;
	
	friend PhysicsObjectFactory;
};

class PhysicsObject;
typedef std::list<PhysicsObject*> PhysicsObjectList;

	}
}