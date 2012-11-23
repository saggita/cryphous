#ifndef __BACKGROUND_RENDERER_H__
#define __BACKGROUND_RENDERER_H__

#include "OffScreenRendererBase.h"
#include "TextureObject.h"
#include "PolygonModel.h"
#include <memory>

namespace Amorphous{
	namespace Shader{
		
class BackGroundRenderer : public Amorphous::Shader::OffScreenRendererBase
{
public:
	BackGroundRenderer(const int width, const int height, const float& intensity);

	~BackGroundRenderer(void);

	void setBackGround(TextureObject* texture);

	void setSolidModels(std::vector<PolygonModel>* solidModels) { this->solidModels = solidModels; }

protected:
	virtual void onRender();

	virtual void onInit();

private:
	void drawBackGround();

	void drawSolid();

private:
	std::auto_ptr<TextureObject> textureObject;
	PolygonModel polygonModel;
	std::vector<PolygonModel>* solidModels;
	const float& intensity;
};

	}
}

#endif