#pragma once

namespace Crystal{
	namespace Command{

public ref class ImportSettingCommand
{
public:
	ImportSettingCommand();

	void setTextBox( 
		System::Windows::Forms::TextBox^ textBoxInputFileName,
		System::Windows::Forms::TextBox^ textBoxInputInterval){
			this->textBoxInputFileName = textBoxInputFileName,
			this->textBoxInputInterval = textBoxInputInterval;
			interval = 1;
	}

	void setFileName();

	void resetFileName() { fileName = ""; }

	int getInterval() { return interval; }

	System::String^ getFileName(){ return fileName; }

	void save();

	void display();

private:
	System::String^ fileName;
	System::Windows::Forms::TextBox^ textBoxInputFileName;
	System::Windows::Forms::TextBox^ textBoxInputInterval;
	int interval;
};

	}
}