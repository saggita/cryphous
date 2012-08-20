#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <boost/noncopyable.hpp>

#include "OpenGLWrapper.h"
#include "GraphicsSettings.h"

namespace Crystal{
	namespace Geom{
		class Box;
	}
	namespace Physics{
		class PhysicsObjectFactory;
	}
	namespace Graphics{

class Renderer : private boost::noncopyable
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

	void init();

	void rendering(Physics::PhysicsObjectFactory *factory, const int width, const int height, const Geom::Box& boundaryBox);

protected:

	void drawBoundaryBox(const Geom::Box& box);

private:
	OpenGLWrapper openGLWrapper;
	const GraphicsSettings& settings;
};

	}
}

#endif