#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "OpenGLWrapper.h"

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
	}
	namespace Shader{
		class PointSpriteRenderer;
		class OnScreenRenderer;
		class DepthRenderer;
		class DepthSmoothingRenderer;
		class ScreenSpaceFluidRenderer;

class Renderer : private Uncopyable
{
public:
	Renderer()
	{
	}

	~Renderer()
	{
	}

	void setPictureBox( HWND pictureBoxHandle ) {
		openGLWrapper.setHandle( pictureBoxHandle );
		init();
	}

	void init();

	void rendering(Physics::PhysicsObjectFactory *factory, const int width, const int height, const Geom::Box& boundaryBox);

private:
	OpenGLWrapper openGLWrapper;

	PointSpriteRenderer* pointSpriteRenderer;
	OnScreenRenderer* onScreenRenderer;
	DepthRenderer* depthRenderer;
	DepthSmoothingRenderer* depthSmoothingRenderer;
	ScreenSpaceFluidRenderer* screenSpaceFluidRenderer;
};

	}
}

#endif