#pragma once

#include "AnimationCommandBase.h"

namespace Crystal{
	namespace Command{

public ref class SimulationCommand : public AnimationCommandBase
{
public:
	SimulationCommand(void);

	~SimulationCommand(){};

	virtual void refresh() override;

	virtual void proceed() override;

	virtual int getStep() override;
};

	}
}