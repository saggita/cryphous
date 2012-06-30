#pragma once

#include "ParticleMarshaler.h"

namespace Crystal{
	namespace Command{

public ref class SimulationCommand
{
public:
	SimulationCommand(void);

	~SimulationCommand(){};

	void refresh();

	void proceed();

	int getStep();

	System::Collections::Generic::List<ManagedPosition^>^ getManagedParticles();
};

	}
}