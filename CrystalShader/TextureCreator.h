#ifndef __TEXTURE_CREATOR_H__
#define __TEXTURE_CREATOR_H__

#include <vector>

namespace Amorphous{
	namespace Color {

class TextureCreator
{
public:

	TextureCreator(void);

	~TextureCreator(void);

	void createTexture(const int size);

	std::vector<unsigned char> getTexture() { return bitmap; }

private:
	std::vector<unsigned char> bitmap;
};

	}
}
#endif __TEXTURE_CREATOR_H__