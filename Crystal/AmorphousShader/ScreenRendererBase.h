#ifndef __SCREEN_RENDERER_BASE_H__
#define __SCREEN_RENDERER_BASE_H__

#include "GLSLMatrix.h"
#include "ShaderObject.h"

namespace Crystal{
	namespace Shader{

class FrameBufferObject;

class ScreenRendererBase
{
public:
	ScreenRendererBase(const int width, const int height);

	virtual ~ScreenRendererBase(void);

	void init();

	void render();

	void render(const FrameBufferObject& frameBufferObject);

	void move(const float x, const float y, const float z);

	void rotate(const float xAngle, const float yAngle, const float zAngle);

protected:
	virtual void onRender() = 0;

	virtual void onInit() = 0;

	int getWidth() const { return width; }

	int getHeight() const { return height; }

	GLSLMatrix getModelviewMatrix();

	GLSLMatrix projectionMatrix;
	
	ShaderObject shaderObject;

private:
	const int width;
	const int height;
};

	}
}

#endif