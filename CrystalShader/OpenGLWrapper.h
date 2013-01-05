#ifndef __OPENGL_WRAPPER_H__
#define __OPENGL_WRAPPER_H__

#include "GLee.h"

namespace Crystal{
	namespace Shader {

class OpenGLWrapper
{
public:
	OpenGLWrapper() {};

	OpenGLWrapper( HWND hWnd );

	~OpenGLWrapper(void);

	void setHandle( HWND hWnd );

private:
	int SetupPixelFormat( HDC hdc );

private:
	HWND hWnd;
	HDC hDC;
	HGLRC hGLRC;

public:
	void SetCurrentRenderingContext() {
		wglMakeCurrent( hDC, hGLRC );
	}

	void BeginRendering() {
		wglMakeCurrent( hDC, hGLRC );
	}

	void EndRendering() {
		SwapBuffers( hDC );
		wglMakeCurrent( hDC, 0);
	}

};

	}
}
#endif