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

	System::Collections::Generic::List<System::Collections::Generic::List<ManagedPosition^>^>^ getManagedPositions();

	System::Collections::Generic::List<System::Collections::Generic::List<ManagedVector^>^>^ getManagedNormals();
};

	}
}