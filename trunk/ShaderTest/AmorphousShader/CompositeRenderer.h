#ifndef __COMPOSITE_RENDERER_H__
#define __COMPOSITE_RENDERER_H__

#include "OffScreenRendererBase.h"
#include "ShaderObject.h"
#include "GLSLMatrix.h"

namespace Amorphous{
	namespace Shader{

class CompositeRenderer : public OffScreenRendererBase
{
public:
	CompositeRenderer(const int width, const int height);

	CompositeRenderer(TextureObject* texture0, TextureObject* texture1);

	~CompositeRenderer(void){};

	void setTextureObject(TextureObject* texture0, TextureObject* texture1);

protected:
	virtual void onRender();

	virtual void onInit();

	virtual void onMove( const float x, const float y, const float z) {};

	virtual void onRotate( const float xAngle, const float yAngle, const float zAngle) {};

private:
	TextureObject* texture0;
	TextureObject* texture1;
};

	}
}

#endif