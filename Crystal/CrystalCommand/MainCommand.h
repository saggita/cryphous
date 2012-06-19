#pragma once

namespace Crystal{
	namespace Command {

ref class ExportSettingCommand;
ref class ChemicalReactingSettingCommand;
ref class ImageExportCommand;
ref class ParticleExportCommand;
ref class ProfileInfoCommand;
ref class GraphicsSettingCommand;
ref class AnimationCommandBase;

public ref class MainCommand
{
public:
	MainCommand(System::Windows::Forms::PictureBox^ pictureBox);

	~MainCommand(void);

	GraphicsSettingCommand^ getGraphicsSettingCommand(){ return graphicsSettingCommand; }

	void proceedSimulation();

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

private:
	ExportSettingCommand^ particleExportSettingCommand;
	ParticleExportCommand^ particleExportCommand;
	GraphicsSettingCommand^ graphicsSettingCommand;
	ProfileInfoCommand^ profileInfoCommand;
	System::Windows::Forms::PictureBox^ pictureBox;
	AnimationCommandBase^ animationCommandBase;
};

	}
}

