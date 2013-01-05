#include "GLee.h"
#include "OpenGLWrapper.h"

using namespace Crystal::Shader;

OpenGLWrapper::OpenGLWrapper(HWND hWnd)
{
	setHandle( hWnd );
}

void OpenGLWrapper::setHandle(HWND hWnd)
{
	this->hWnd = hWnd;
	hDC = GetDC( this->hWnd );
	if( 0 != SetupPixelFormat( hDC ) ) return;
	
	hGLRC = wglCreateContext(hDC); 
}

int OpenGLWrapper::SetupPixelFormat(HDC hDC)
{
	static PIXELFORMATDESCRIPTOR pfd = {
		sizeof (PIXELFORMATDESCRIPTOR),		// 構造体のサイズ
		1,									// OpenGL バージョン
		PFD_DRAW_TO_WINDOW |				// ウィンドウスタイル
		PFD_SUPPORT_OPENGL |				// OpenGL を使う
		PFD_DOUBLEBUFFER,					// ダブルバッファ
		PFD_TYPE_RGBA,						// ピクセルのカラーデータ
		32,									// 色のビット数
		0, 0, 0, 0, 0, 0, 0, 0,				// RGBAカラーバッファのビット
		0, 0, 0, 0, 0,						// アキュムレーションバッファのピクセル当りのビット数
		32,									// デプスバッファ    のピクセル当りのビット数
		0,									// ステンシルバッファのピクセル当りのビット数
		0,									// 補助バッファ      のピクセル当りのビット数
		PFD_MAIN_PLANE,						// レイヤータイプ
		0,									// 
		0,									// 
		0,									// 
		0									// 
	};

	const int pixelformat = ChoosePixelFormat( hDC, &pfd);
    
	if ( 0 == pixelformat ) {
		return 1;
	}
	else if ( FALSE == SetPixelFormat(hDC, pixelformat, &pfd) ) {
		return 2;
	}

	return 0;
}

OpenGLWrapper::~OpenGLWrapper(void)
{
	wglMakeCurrent(0, 0); 
	wglDeleteContext(hGLRC);
	ReleaseDC( hWnd, hDC );
}
