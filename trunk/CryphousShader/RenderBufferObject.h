#ifndef __RENDER_BUFFER_OBJECT_H__
#define __RENDER_BUFFER_OBJECT_H__

namespace Cryphous
{
	namespace Shader{

class TextureObject;

class RenderBufferObject
{
public:
	RenderBufferObject(const int width, const int height, const bool appendDepth);

	~RenderBufferObject(void);

	unsigned int getID() const { return id; }

	TextureObject& getTextureObject(){ return *textureObject; }

	TextureObject& getDepthTextureObject() { return *depthTextureObject; }

	int getWidth() const;

	int getHeight() const;

private:

	void init();

	unsigned int id;

	TextureObject* textureObject;

	TextureObject* depthTextureObject;
};

	}
}

#endif