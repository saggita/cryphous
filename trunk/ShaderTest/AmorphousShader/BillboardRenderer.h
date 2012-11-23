#ifndef __BILLBOARD_RENDERER_H__
#define __BILLBOARD_RENDERER_H__

#include "OffScreenRendererBase.h"
#include "TextureObject.h"
#include "VisualParticle.h"
#include <memory>

namespace Amorphous{
	namespace Shader{

class BillboardRenderer : public OffScreenRendererBase
{
public:
	BillboardRenderer(const int width, const int height, const float& size, const float& alpha);

	~BillboardRenderer(void);

	void setVisualParticles(const Amorphous::Color::VisualParticleList& visualParticles);

protected:
	virtual void onRender();

	virtual void onInit();

	virtual void onIdle(){};

private:
	std::auto_ptr<TextureObject> alphaTexture;
	std::vector<double> positions;
	std::vector<double> colors;

	const float& size;
	const float& alpha;
	
	void initColorTransferTexture();
};

	}
}
#endif