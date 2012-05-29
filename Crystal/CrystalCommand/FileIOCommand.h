#pragma once

namespace Crystal{
	namespace Command{

public ref class FileIOCommand
{
public:
	FileIOCommand(void);

	bool fileOpen();

	bool fileOpen( System::String^ path );

	bool fileSave();

	bool fileSave( System::String^ path );

	bool fileSaveOverride();

	System::String^ getFileName() { return fileName; }

private:
	System::String^ fileName;
};

	}
}
