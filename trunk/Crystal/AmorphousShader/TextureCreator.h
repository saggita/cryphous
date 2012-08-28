#ifndef __TEXTURE_CREATOR_H__
#define __TEXTURE_CREATOR_H__

#include <vector>

namespace Crystal{
	namespace Shader {

class TextureCreator
{
public:

	TextureCreator(void);

	~TextureCreator(void);

	void createTexture(const int size, const bool addNoise = true);

	std::vector<unsigned char> getTexture() { return bitmap; }

private:
	std::vector<unsigned char> bitmap;
};

	}
}
#endif __TEXTURE_CREATOR_H__