#ifndef __FRAME_BUFFER_OBJECT_H__
#define __FRAME_BUFFER_OBJECT_H__

namespace Crystal {
	namespace Graphics {

class TextureObject;
class RenderBufferObject;

class FrameBufferObject
{
public:
	FrameBufferObject(const int width, const int height);
	
	~FrameBufferObject(void);

	unsigned int getID() const { return id; }

	int getWidth() const;

	int getHeight() const;

	TextureObject* getTextureObject();

private:
	void init();

	unsigned int id;

	RenderBufferObject* renderBufferObject;
};

	}
}

#endif