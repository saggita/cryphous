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
	ScreenRendererBase();

	void setWidth(const int width) { this->width = width; }

	void setHeight(const int height) { this->height = height; }

	int getWidth() const { return width; }

	int getHeight() const { return height; }

	virtual ~ScreenRendererBase(void);

	void init();

	void move(const float x, const float y, const float z);

	void rotate(const float xAngle, const float yAngle, const float zAngle);

protected:
	virtual void onRender() = 0;

	virtual void onInit() = 0;

	GLSLMatrix getModelviewMatrix();

	GLSLMatrix projectionMatrix;
	
	ShaderObject shaderObject;

private:
	int width;
	int height;
};

	}
}

#endif