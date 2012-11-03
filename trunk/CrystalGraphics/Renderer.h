#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "OpenGLWrapper.h"
#include "GraphicsSettings.h"

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "Renderer.h"

#include "../CrystalPhysics/Uncopyable.h"

#include <cassert>
#include <cmath>
#include <cstdlib>

namespace Crystal{
	namespace Geom{
		class Box;
	}
	namespace Physics{
		class PhysicsObjectFactory;
		class LightSourceFactory;
	}
	namespace Graphics{

class Renderer : private Uncopyable
{
public:
	Renderer(const GraphicsSettings& settings) :
	  settings(settings)
	{
	}

	~Renderer()
	{
	}

	void setPictureBox( HWND pictureBoxHandle ) {
		openGLWrapper.setHandle( pictureBoxHandle );
		init();
	}

	void init() { openGLWrapper.SetCurrentRenderingContext(); }

	void rendering(Physics::PhysicsObjectFactory *factory, Physics::LightSourceFactory* lightSourceFactory, const int width, const int height, const Geom::Box& boundaryBox);

protected:

	void drawBoundaryBox(const Geom::Box& box);

private:
	OpenGLWrapper openGLWrapper;
	const GraphicsSettings& settings;
};

	}
}

#endif