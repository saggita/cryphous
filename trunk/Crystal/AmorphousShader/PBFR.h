#ifndef __RBFR_H__
#define __PBFR_H__

#include <boost/noncopyable.hpp>
#include <vector>
#include <list>
#include <memory>

#include "OnScreenRendererBase.h"
#include "PBFRSetting.h"
#include "OpenGLWrapper.h"
#include "VisualParticle.h"

namespace Crystal{
	namespace Shader{
		class PointRenderer;
		class CompositeRenderer;
		class BackGroundRenderer;
		
class PBFR : public OnScreenRendererBase
{
public:
	PBFR(const int width, const int height, const PBFRSetting& setting);

	~PBFR();

	void setVisualParticle( const VisualParticleVector& vps ) { visualParticles = vps; }

protected:

	virtual void onRender();

	virtual void onInit();

	virtual void onIdle() {};

private:

	PointRenderer* pointRenderer;
	CompositeRenderer* compositeRenderer;
	std::vector<double> points;
	PBFRSetting setting;
	OpenGLWrapper openGLWrapper;
	VisualParticleVector visualParticles;
};

	}
}
#endif