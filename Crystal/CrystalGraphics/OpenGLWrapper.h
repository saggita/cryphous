#pragma once

#include <windows.h>
#include <GL/gl.h>

namespace Crystal{
	namespace Graphics {

class OpenGLWrapper
{
public:
	OpenGLWrapper() {};

	OpenGLWrapper( HWND hWnd );

	void setHandle( HWND hWnd );

	~OpenGLWrapper(void);

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