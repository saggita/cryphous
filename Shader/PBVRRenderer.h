#ifndef __CRYSTAL_PBVR_RENDERER_H__
#define __CRYSTAL_PBVR_RENDERER_H__

#include "OffScreenRendererBase.h"

#include "VisualParticle.h"
#include <memory>

namespace Crystal{
	namespace Shader{

class PBVRRenderer : public OffScreenRendererBase
{
public:
	PBVRRenderer(float& size, float& alpha);

	~PBVRRenderer(void);

	void setVisualParticles(const std::vector<float>& positions, const std::vector<float>& colors) {
		this->positions = positions;
		this->colors = colors;
	}

protected:
	virtual void onRender();

	virtual void onInit();

	virtual void onIdle(){};

private:
	std::vector<float> positions;
	std::vector<float> colors;

	float& size;
	float& alpha;
	
	void initColorTransferTexture();
};

	}
}
#endif