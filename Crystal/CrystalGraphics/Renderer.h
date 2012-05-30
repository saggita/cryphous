#pragma once

#include <boost/noncopyable.hpp>
#include <vector>

#include "OpenGLWrapper.h"
#include "Texture.h"

namespace Crystal{
	namespace Physics{
		class PhysicsObjectFactory;
	}
	namespace Graphics{
		class VisualPrimitiveFactory;
		class Texture;

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

	void rendering(Physics::PhysicsObjectFactory *factory, const int width, const int height);

protected:

	void drawBoundaryBox();

private:
	OpenGLWrapper openGLWrapper;
};

	}
}