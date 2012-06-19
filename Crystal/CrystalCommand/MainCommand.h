#pragma once

namespace Crystal{
	namespace Command {

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
ref class GraphicsSettingCommand;
ref class AnimationCommandBase;

public ref class MainCommand
{
public:
	MainCommand(System::Windows::Forms::PictureBox^ pictureBox);

	~MainCommand(void);

	void proceedSimulation();

	SimulationSettingCommand^ getSimulationSettingCommand() { return simulationSettingCommand; }

	ObjectSettingCommand^ getObjectSettingCommand() { return objectSettingCommand; }

	FileIOCommand^ getFileIOCommand() { return fileIOCommand; }

	ParticleInfoCommand^ getParticleInfoCommand() { return particleInfoCommand; }

	BoundarySettingCommand^ getBoundarySettingCommand() { return boundarySettingCommand; }

	ExportSettingCommand^ getParticleExportSettingCommand() { return particleExportSettingCommand; }

	ParticleExportCommand^ getParticleExportCommand() { return particleExportCommand; }

	void refreshSimulation();

	void rendering();

	void displayInformation(System::Windows::Forms::ListBox^ listBox);

	void rotateX(int angle);

	void rotateY(int angle);

	void rotateZ(int angle);

	void zoom(double zoom);

	void move(double x, double y);

	void viewReset();

	GraphicsSettingCommand^ getGraphicsSettingCommand(){ return graphicsSettingCommand; }

private:
	SimulationSettingCommand^ simulationSettingCommand;
	ObjectSettingCommand^ objectSettingCommand;
	FileIOCommand^ fileIOCommand;
	ParticleInfoCommand^ particleInfoCommand;
	BoundarySettingCommand^ boundarySettingCommand;
	ExportSettingCommand^ particleExportSettingCommand;
	ParticleExportCommand^ particleExportCommand;
	GraphicsSettingCommand^ graphicsSettingCommand;
	ProfileInfoCommand^ profileInfoCommand;
	System::Windows::Forms::PictureBox^ pictureBox;
	AnimationCommandBase^ animationCommandBase;
};

	}
}

