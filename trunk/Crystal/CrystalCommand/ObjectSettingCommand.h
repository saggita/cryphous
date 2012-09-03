#pragma once

#include "ParticleMarshaler.h"

namespace Crystal{
	namespace Command{

public ref class ObjectSettingCommand
{
private:
	System::Windows::Forms::DataGridView ^view;

public:
	ObjectSettingCommand();

	~ObjectSettingCommand();

	void refresh();

	void createPhysicsObject(System::String^ type, const float density, const float pressureCoe, const float viscosityCoe, System::Collections::Generic::List<ManagedPosition^>^ managedPosition);

	void addParticles(int index, System::Collections::Generic::List<ManagedPosition^>^ managedPosition, System::Collections::Generic::List<ManagedPosition^>^ managedVelocity);
};

	}
}