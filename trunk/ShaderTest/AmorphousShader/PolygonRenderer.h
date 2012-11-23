#ifndef __POLYGON_RENDERER_H__
#define __POLYGON_RENDERER_H__

#include "OffScreenRendererBase.h"
#include "PolygonModel.h"
#include "TextureObject.h"
#include <memory>

namespace Amorphous{
	namespace Shader{
		class FrameBufferObject;

class PolygonRenderer : public Amorphous::Shader::OffScreenRendererBase
{
public:
	PolygonRenderer(const int width, const int height, const std::string& polygonFileName);

	~PolygonRenderer(void);

protected:
	virtual void onRender();

	virtual void onInit();

private:
	Amorphous::Shader::PolygonModel polygonModel;
	std::auto_ptr<TextureObject> textureObject;
	const std::string polygonFileName;
};

	}
}

#endif