#ifndef __POINT_RENDERER_H__
#define __POINT_RENDERER_H__

#include "ScreenRendererBase.h"
#include "TextureObject.h"
#include "GLSLMatrix.h"
#include "PBFRSetting.h"
#include "VisualParticle.h"

namespace Crystal{
	namespace Shader{

class PointRenderer : public ScreenRendererBase
{
public:
	PointRenderer(const int width, const int height, const PBFRSetting& setting);

	~PointRenderer(void);

	void initRepetitionLevel() { repetitionLevel = 0; }

	void setVisualParticles(const VisualParticleVector& visualParticles);

protected:
	virtual void onRender();

	virtual void onInit();

private:
	std::auto_ptr<TextureObject> noiseTexture;
	std::auto_ptr<TextureObject> alphaTexture;
	std::vector<double> positions;
	std::vector<double> colors;
	const PBFRSetting& setting;
	int repetitionLevel;
	
	void initNoiseTexture();

	void initColorTransferTexture();
};

	}
}
#endif