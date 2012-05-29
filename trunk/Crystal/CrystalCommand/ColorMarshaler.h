#pragma once

namespace Crystal{
	namespace Graphics{
		class Color4d;
	}
	namespace Command{

public ref class ColorMarshaler
{
public:
	ColorMarshaler(void);

	static System::Drawing::Color convertToDrawingColor(const Graphics::Color4d& src);

	static Graphics::Color4d convertToColor4d(System::Drawing::Color^ src);
};

	}
}
