#ifndef __PBVR_H__
#define __PBVR_H__

#include "OffScreenRendererBase.h"
#include "VisualParticle.h"
#include <memory>

namespace Cryphous{
	namespace Shader{

class PBVR : public OffScreenRendererBase
{
public:
	PBVR(const int width, const int height, float& size, float& alpha);

	~PBVR(void);

	void setVisualParticles(const VisualParticleList& visualParticles);

protected:
	virtual void onRender();

	virtual void onInit();

	virtual void onIdle(){};

private:
	std::vector<double> positions;
	std::vector<double> colors;

	float& size;
	float& alpha;
};

	}
}
#endif