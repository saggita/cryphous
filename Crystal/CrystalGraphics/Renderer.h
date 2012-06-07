#pragma once

#include <boost/noncopyable.hpp>
#include <vector>

#include "OpenGLWrapper.h"

namespace Crystal{
	namespace Geom{
		class Box;
	}
	namespace Physics{
		class PhysicsObjectFactory;
	}
	namespace Graphics{
		class VisualPrimitiveFactory;
		
class Renderer : private boost::noncopyable
{
private:
	Renderer();

	~Renderer();

public:
	
	static Renderer* get() {
		static Renderer renderer;
		return &renderer;
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
};

	}
}