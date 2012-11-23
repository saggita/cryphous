#ifndef __FLAME_RENDERER_BASE_H__
#define __FLAME_RENDERER_BASE_H__

#include <boost/noncopyable.hpp>
#include <vector>
#include <list>
#include <memory>

#include "OpenGLWrapper.h"
#include "../AmorphousColor/VisualParticle.h"
#include "../AmorphousColor/Texture.h"
#include "OnScreenRendererBase.h"
#include "PBFRSetting.h"
#include "BackGroundRenderer.h"

namespace Amorphous{
	namespace Shader{
		class BackGroundRenderer;
		class PolygonModel;

class FlameRendererBase : public OnScreenRendererBase
{
public:
	FlameRendererBase(const int width, const int height, const PBFRSetting& setting);

	virtual ~FlameRendererBase();

	void setPictureBox( HWND pictureBoxHandle, const int width, const int height ) {
		openGLWrapper.setHandle( pictureBoxHandle );
		init();
	}

	void setup(Color::VisualParticleList* visualParticles, std::vector<Amorphous::Shader::PolygonModel>* solidModels);

	OpenGLWrapper* getOpenGLWrapper() { return &openGLWrapper; }

	virtual bool isBillboard() = 0;

	void setBackGround(const Amorphous::Color::Texture& texture);

protected:

	virtual void onRender() = 0;

	virtual void onIdle(){};

	virtual void onInit() = 0;

	void applyBlur();

protected:
	Color::VisualParticleList* visualParticles;
	const PBFRSetting& setting;
	OpenGLWrapper openGLWrapper;
	BackGroundRenderer backGroundRenderer;
};

	}
}
#endif