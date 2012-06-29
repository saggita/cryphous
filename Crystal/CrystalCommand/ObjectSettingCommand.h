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

	void setView(System::Windows::Forms::DataGridView ^view){ this->view = view; }

	void displaySettings();

	void saveSettings(const double density, const double pressureCoe, const double viscosityCoe, System::Collections::Generic::List<ManagedPosition^>^ managedPosition);

	void addObject();

	void deleteObject();
};

	}
}