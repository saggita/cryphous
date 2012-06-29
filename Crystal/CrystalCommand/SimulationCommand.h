#pragma once

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
};

	}
}