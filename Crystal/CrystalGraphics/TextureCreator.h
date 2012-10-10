#ifndef __TEXTURE_CREATOR_H__
#define __TEXTURE_CREATOR_H__

namespace Crystal{
	namespace Graphics {

class TextureCreator
{
public:

	TextureCreator(void);

	~TextureCreator(void);

	void createTexture(const int size);

	void createNoiseTexture(const int size);

	bool destroyTexture();

	unsigned char* getTexture() { return bitmap; }

private:
	unsigned char* bitmap;
};

	}
}

#endif