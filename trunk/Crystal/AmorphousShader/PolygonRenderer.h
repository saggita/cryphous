#ifndef __POLYGON_RENDERER_H__
#define __POLYGON_RENDERER_H__

#include "OffScreenRendererBase.h"
#include "PolygonModel.h"
#include "TextureObject.h"
#include "PBFRSetting.h"
#include <memory>

namespace Crystal{
	namespace Shader{
		class FrameBufferObject;

class PolygonRenderer : public Crystal::Shader::OffScreenRendererBase
{
public:
	PolygonRenderer(const int width, const int height, const std::string& polygonFileName, const PBFRSetting& setting);

	~PolygonRenderer(void);

protected:
	virtual void onRender();

	virtual void onInit();

private:
	Crystal::Shader::PolygonModel polygonModel;
	std::auto_ptr<TextureObject> textureObject;
	const std::string polygonFileName;
	const PBFRSetting& setting;
};

	}
}

#endif