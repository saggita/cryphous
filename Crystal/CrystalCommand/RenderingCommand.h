#pragma once

using namespace System::Drawing;

namespace Crystal{
	namespace Command{

public ref class RenderingCommand
{
public:
	RenderingCommand(void);

	Bitmap^ getImage(int width, int height);
};


	}
}