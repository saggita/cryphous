#include "FileIOCommand.h"

#include "ApplicationSettings.h"

using namespace Crystal::Command;

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Xml;

FileIOCommand::FileIOCommand(void)
{
}

bool FileIOCommand::fileOpen()
{
	OpenFileDialog^ dialog = gcnew OpenFileDialog();
	dialog->Filter = "crystal files(*.crystal)|*.crystal|all files(*.*)|*.*";
	if( dialog->ShowDialog() !=
		System::Windows::Forms::DialogResult::OK ) {
			return false;
	}
	fileName = dialog->FileName;
	return fileOpen( dialog->FileName );
}

bool FileIOCommand::fileOpen(String^ path)
{
	//ApplicationSettings^ applicationSettings = gcnew ApplicationSettings();
	XmlDocument^ doc = gcnew XmlDocument();
	doc->Load( path );
	fileName = path;
	return ApplicationSettings::get()->readFromXML( doc );
}

bool FileIOCommand::fileSave()
{
	SaveFileDialog^ dialog = gcnew SaveFileDialog();
	dialog->Filter = "crystal files(*.crystal)|*.crystal|all files(*.*)|*.*";
	if( dialog->ShowDialog() !=
		System::Windows::Forms::DialogResult::OK ) {
			return false;
	}
	return fileSave( dialog->FileName );
}

bool FileIOCommand::fileSave(String ^path)
{
	//ApplicationSettings^ applicationSettings = gcnew ApplicationSettings();
	ApplicationSettings::get()->writeToXML()->Save( path );
	fileName = path;
	return true;
}

bool FileIOCommand::fileSaveOverride()
{
	return (fileName == "") ? fileSave() : fileSave( fileName );
}