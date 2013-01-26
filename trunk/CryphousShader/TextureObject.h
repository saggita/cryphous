#ifndef __TEXTURE_OBJECT_H__
#define __TEXTURE_OBJECT_H__

#include "GLee.h"
#include <vector>

namespace Cryphous{
	namespace Shader{

class TextureObject
{
public:
	enum Type{
		RGBATexture,
		AlphaTexture,
		DepthTexture
	};

	TextureObject(const int width, const int height);

	TextureObject(const std::vector<GLubyte>& pixels, const int width, const int height);

	TextureObject(const std::vector<GLfloat>& pixels, const int width, const int height);

	~TextureObject(void);

	unsigned int getID() const { return id; }
	
	unsigned int getUnitID() const { return unitID; }

	int getWidth() const { return width; }

	int getHeight() const { return height; }

	void apply(const unsigned int unitID);

	void release();

	void initAlphaTexture(const std::vector<GLubyte>& alphas, const int width, const int height);

	void initDepthTexture(const int width, const int height);

	Type getType() const { return type; }
	
private:
	unsigned int id;
	int width;
	int height;
	unsigned int unitID;
	Type type;

	void init(const int width, const int height);

	void init(const std::vector<GLubyte>& pixels, const int width, const int height);

	void init(const std::vector<GLfloat>& pixels, const int width, const int height);
};

	}
}
#endif