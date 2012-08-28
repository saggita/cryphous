#ifndef __SMOKE_TEXTURE_CREATOR_H__
#define __SMOKE_TEXTURE_CREATOR_H__

namespace Crystal{
	namespace Color{

class SmokeTextureCreator
{
public:
	SmokeTextureCreator(void);

	~SmokeTextureCreator(void);

	bool createTexture(const int size);

	bool destroyTexture();

	unsigned char* getTexture() { return bitmap; }

private:
	unsigned char* bitmap;

private:
	double calculateHenyeyGreensteinFunction(const double g, const double innerProduct);
};

	}
}
#endif __SMOKE_TEXTURE_CREATOR_H__