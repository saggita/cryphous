#pragma once

namespace Crystal{
	namespace Command {

ref class ProfileInfoCommand;
ref class GraphicsSettingCommand;
ref class SimulationCommand;

public ref class MainCommand
{
public:
	MainCommand(System::Windows::Forms::PictureBox^ pictureBox, System::String^ productName);

	~MainCommand(void);

	SimulationCommand^ getSimulationCommand() { return simulationCommand; }

	GraphicsSettingCommand^ getGraphicsSettingCommand(){ return graphicsSettingCommand; }

	void proceedSimulation();

	void refreshSimulation();

	void rendering();

	void displayInformation(System::Windows::Forms::ListBox^ listBox);

	void rotateX(int angle);

	void rotateY(int angle);

	void rotateZ(int angle);

	void zoom(float zoom);

	void move(float x, float y);

	void viewReset();

private:
	GraphicsSettingCommand^ graphicsSettingCommand;
	ProfileInfoCommand^ profileInfoCommand;
	System::Windows::Forms::PictureBox^ pictureBox;
	SimulationCommand^ simulationCommand;
	System::String^ productName;
};

	}
}

