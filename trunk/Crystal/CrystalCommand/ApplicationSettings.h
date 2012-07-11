#pragma once

#include <list>

namespace Crystal {
	namespace Physics {
		class PhysicsObjectFactory;
		struct PhysicsObjectCondition;
		class SimulationSetting;
		class Simulation;
	}
	namespace Graphics {
		class Renderer;
	}

	namespace Command {

public ref class ApplicationSettings
{	
private:
	ApplicationSettings(void);

	~ApplicationSettings();

	static ApplicationSettings^ instance;

public:
	static ApplicationSettings^ get() {
		if( instance == nullptr ) {
			instance =  gcnew ApplicationSettings();
		}
		return instance;
	}

	void refresh();

public:

	double getParticleDiameter();

	void setParticleDiameter(const double diameter);

	Physics::PhysicsObjectFactory* factory;

	Physics::SimulationSetting* simulationSetting;

	Physics::Simulation* simulation;

	Graphics::Renderer* renderer;

	std::list<Physics::PhysicsObjectCondition>* conditions;

};

	}
}