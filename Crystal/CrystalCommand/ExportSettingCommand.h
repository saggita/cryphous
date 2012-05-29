#pragma once

namespace Crystal{
	namespace Command{

public ref class ExportSettingCommand
{
public:
	ExportSettingCommand(System::String^ filterName, System::String^ filterExtension);

	void setTextBox( 
		System::Windows::Forms::TextBox^ textBoxOutputInterval,
		System::Windows::Forms::TextBox^ textBoxOutputFileName ){
			this->textBoxOutputInterval = textBoxOutputInterval;
			this->textBoxOutputFileName = textBoxOutputFileName;
	}

	void setFileName();

	void resetFileName() { fileName = ""; }

	System::String^ getFileName() { return this->fileName; }

	System::String^ getBaseFileName();

	System::String^ getExtension() { return filterExtension; }

	void save();

	void display();

	bool isSaveTimeStep(const int step);

private:
	System::String^ fileName;
	int outputInterval;
	System::Windows::Forms::TextBox^ textBoxOutputInterval;
	System::Windows::Forms::TextBox^ textBoxOutputFileName;
	System::String^ filterName;
	System::String^ filterExtension;
};

	}
}