#pragma once

namespace Crystal{
	namespace Command {

ref class ExportSettingCommand;
ref class GraphicsSettingCommand;
ref class BoundarySettingCommand;
ref class FileIOCommand;
ref class ImageExportCommand;
ref class AnimationCommandBase;
ref class ProfileExportCommand;
ref class ProfileInfoCommand;

public ref class MainCommandBase abstract
{
public:
	MainCommandBase(System::Windows::Forms::PictureBox^ pictureBox);

	virtual ~MainCommandBase(void);

	virtual void refreshSimulation();

	virtual void proceedSimulation();

	void rendering();

	void displayInformation(System::Windows::Forms::ListBox^ listBox);

	void rotateX(int angle);

	void rotateY(int angle);

	void rotateZ(int angle);

	void zoom(double zoom);

	void move(double x, double y);

	void viewReset();

	ExportSettingCommand^ getExportSettingCommand(){ return exportImagesSettingCommand; }

	GraphicsSettingCommand^ getGraphicsSettingCommand(){ return graphicsSettingCommand; }

	FileIOCommand^ getFileIOCommand() { return fileIOCommand; }

	ExportSettingCommand^ getProfileExportSettingCommand() { return profileExportSettingCommand; }

	ProfileExportCommand^ getProfileExportCommand() { return profileExportCommand; }

private:
	ExportSettingCommand^ exportImagesSettingCommand;
	GraphicsSettingCommand^ graphicsSettingCommand;
	FileIOCommand^ fileIOCommand;
	ExportSettingCommand^ profileExportSettingCommand;
	ProfileExportCommand^ profileExportCommand;
	ProfileInfoCommand^ profileInfoCommand;
	System::Windows::Forms::PictureBox^ pictureBox;

protected:
	AnimationCommandBase^ animationCommandBase;
};

	}
}

