#pragma once

namespace Crystal{
	namespace Graphics{
		class Texture;
	}
	namespace Command{

public ref class ImageMarshaler {
public:
	static System::Drawing::Bitmap^ convertToBitmap(const Graphics::Texture& src);

	static Graphics::Texture convertToTexture(System::Drawing::Bitmap^ src);
};

	}
}