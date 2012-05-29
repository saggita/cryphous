
#include "ImportSettingCommand.h"

using namespace Crystal::Command;

using namespace System;
using namespace System::Windows::Forms;

ImportSettingCommand::ImportSettingCommand(void)
{
	fileName = "";
}

void ImportSettingCommand::setFileName()
{
	OpenFileDialog^ dialog = gcnew OpenFileDialog();
	dialog->Filter = "全てのファイル(*.*)|*.*";
	if( dialog->ShowDialog() !=
		System::Windows::Forms::DialogResult::OK ) {
			return;
	}
	fileName = dialog->FileName;
}

void ImportSettingCommand::save()
{
	fileName = textBoxInputFileName->Text;
	interval = Convert::ToInt32( textBoxInputInterval->Text );
}

void ImportSettingCommand::display()
{
	textBoxInputFileName->Text = fileName->ToString();
	textBoxInputInterval->Text = interval.ToString();
}