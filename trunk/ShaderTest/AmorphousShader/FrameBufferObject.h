#ifndef __FRAME_BUFFER_OBJECT_H__
#define __FRAME_BUFFER_OBJECT_H__

namespace Amorphous{
	namespace Shader{

class TextureObject;
class RenderBufferObject;

class FrameBufferObject
{
public:
	FrameBufferObject(const int width, const int height, const bool appendDepth);
	
	~FrameBufferObject(void);

	unsigned int getID() const { return id; }

	int getWidth() const;

	int getHeight() const;

	TextureObject& getTextureObject();

	TextureObject& getDepthTextureObject();

private:
	void init();

	unsigned int id;

	const bool appendDepth;

	RenderBufferObject* renderBufferObject;
};

	}
}

#endif