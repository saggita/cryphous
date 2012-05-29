#pragma once

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

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
	HWND hWnd;	///< ウィンドウハンドル.
	HDC hDC;	///< デバイスコンテキストハンドル.
	HGLRC hGLRC;	///< OpenGLハンドル.

public:
	/// レンダリングコンテキストをカレントに設定する.
	void SetCurrentRenderingContext() {
		wglMakeCurrent( hDC, hGLRC );
	}

	/// 描画を開始する.
	void BeginRendering() {
		wglMakeCurrent( hDC, hGLRC );
	}

	/// 描画を終了する.
	void EndRendering() {
		SwapBuffers( hDC );
		wglMakeCurrent( hDC, 0);
	}

};

	}	// namespace UI
}	// namespace Crystal