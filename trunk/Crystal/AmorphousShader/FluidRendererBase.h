#ifndef __FLUID_RENDERER_BASE_H__
#define __FLUID_RENDERER_BASE_H__

#include <boost/noncopyable.hpp>
#include <vector>
#include <list>
#include <memory>

#include "OpenGLWrapper.h"
#include "VisualParticle.h"
#include "Texture.h"
#include "OnScreenRendererBase.h"
#include "PBFRSetting.h"

namespace Crystal{
	namespace Shader{
		class BackGroundRenderer;
		class PolygonModel;

class FluidRendererBase : public OnScreenRendererBase
{
public:
	FluidRendererBase(const int width, const int height, const PBFRSetting& setting);

	virtual ~FluidRendererBase();

	void setPictureBox( HWND pictureBoxHandle, const int width, const int height ) {
		openGLWrapper.setHandle( pictureBoxHandle );
		init();
	}

	void setup(VisualParticleVector* visualParticles) { this->visualParticles = visualParticles;}

	OpenGLWrapper* getOpenGLWrapper() { return &openGLWrapper; }

	virtual bool isBillboard() = 0;

	void setBackGround(const Crystal::Shader::Texture& texture);

protected:

	virtual void onRender() = 0;

	virtual void onIdle(){};

	virtual void onInit() = 0;

protected:
	VisualParticleVector* visualParticles;
	const PBFRSetting& setting;
	OpenGLWrapper openGLWrapper;
};

	}
}
#endif