#include "ExportSettingCommand.h"

using namespace Crystal::Command;

using namespace System;
using namespace System::Windows::Forms;

ExportSettingCommand::ExportSettingCommand(System::String^ filterName, System::String^ filterExtension)
{
	fileName = "";
	outputInterval = 10;

	this->filterName = filterName;
	this->filterExtension = filterExtension;
}

void ExportSettingCommand::setFileName()
{
	SaveFileDialog^ dialog = gcnew SaveFileDialog();
	dialog->Filter = filterName + "(*." + filterExtension + ")|*."+ filterExtension + "|" + "全てのファイル(*.*)|*.*";

	if( dialog->ShowDialog() !=
		System::Windows::Forms::DialogResult::OK ) {
			return;
	}
	this->fileName = dialog->FileName;
}

System::String^ ExportSettingCommand::getBaseFileName()
{
	return System::IO::Path::GetDirectoryName( getFileName() ) + "\\" + System::IO::Path::GetFileNameWithoutExtension( getFileName());	
}

void ExportSettingCommand::save()
{
	this->outputInterval = Convert::ToInt32( this->textBoxOutputInterval->Text );
	this->fileName = this->textBoxOutputFileName->Text;
}

void ExportSettingCommand::display()
{
	this->textBoxOutputInterval->Text = this->outputInterval.ToString();
	this->textBoxOutputFileName->Text = this->fileName->ToString();
}

bool ExportSettingCommand::isSaveTimeStep(const int step)
{
	return (fileName != "") && (step % outputInterval == 0);
}

