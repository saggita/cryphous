#ifndef __CRYSTAL_GRAPHICS_RENDER_BUFFER_OBJECT_H__
#define __CRYSTAL_GRAPHICS_RENDER_BUFFER_OBJECT_H__

namespace Crystal {
	namespace Graphics {

class TextureObject;

class RenderBufferObject
{
public:
	RenderBufferObject( const int width, const int height );

	~RenderBufferObject(void);

	unsigned int getID() const { return id; }

	TextureObject* getTextureObject(){ return textureObject; }

	int getWidth() const;

	int getHeight() const;

private:

	void init();

	unsigned int id;

	TextureObject* textureObject;
};

	}
}

#endif