#pragma once

#include "MainCommandBase.h"

namespace Crystal{
	namespace Command {

ref class AmbientSettingCommand;
ref class ExportSettingCommand;
ref class ChemicalReactingSettingCommand;
ref class SimulationSettingCommand;
ref class ObjectSettingCommand;
ref class BoundarySettingCommand;
ref class FileIOCommand;
ref class ImageExportCommand;
ref class ParticleInfoCommand;
ref class ParticleExportCommand;
ref class ProfileInfoCommand;

public ref class MainCommand : public MainCommandBase
{
public:
	MainCommand(System::Windows::Forms::PictureBox^ pictureBox);

	~MainCommand(void);

	virtual void proceedSimulation() override;

	SimulationSettingCommand^ getSimulationSettingCommand() { return simulationSettingCommand; }

	ObjectSettingCommand^ getObjectSettingCommand() { return objectSettingCommand; }

	FileIOCommand^ getFileIOCommand() { return fileIOCommand; }

	ParticleInfoCommand^ getParticleInfoCommand() { return particleInfoCommand; }

	BoundarySettingCommand^ getBoundarySettingCommand() { return boundarySettingCommand; }

	ExportSettingCommand^ getParticleExportSettingCommand() { return particleExportSettingCommand; }

	ParticleExportCommand^ getParticleExportCommand() { return particleExportCommand; }

private:
	SimulationSettingCommand^ simulationSettingCommand;
	ObjectSettingCommand^ objectSettingCommand;
	FileIOCommand^ fileIOCommand;
	ParticleInfoCommand^ particleInfoCommand;
	BoundarySettingCommand^ boundarySettingCommand;
	ExportSettingCommand^ particleExportSettingCommand;
	ParticleExportCommand^ particleExportCommand;
};

	}
}

