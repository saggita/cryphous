#include "StdAfx.h"
#include <cassert>
#include "../AmorphousShader/GLSLUtility.h"
#include <glut.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <memory>

#include "PolygonRendererTest.h"
#include "DepthRendererTest.h"
#include "BackGroundRendererTest.h"
#include "BillboardRendererTest.h"
#include "../AmorphousShader/OnScreenRendererBase.h"

using namespace Amorphous::Shader;

std::auto_ptr<OnScreenRendererBase> rendererBase;
std::vector<PolygonModel> solidModels;

bool isIdle = true;
int mButton;
int xBegin;
int yBegin;
float distance = 0.0;

const int width = 512;
const int height = 512;

void onDisplay()
{
	rendererBase->render();

	glutSwapBuffers();

	assert( GLSLUtility::hasNoError() );
}

void onIdle()
{
	rendererBase->idle();
	glutPostRedisplay();
}

void onInit()
{
	glutInitWindowPosition(0,0);
	glutInitWindowSize(width, height);
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );

	glutCreateWindow("AmorphousRendererTest");

	Camera::get()->zoom = -0.1f;

	std::vector<Vertex> vertices;
	vertices.push_back( Vertex( 0.0, 0.0, 0.0) );
	vertices.push_back( Vertex( 1.0, 0.0, 0.0) );
	vertices.push_back( Vertex( 1.0, 1.0, 0.0) );

	std::vector<Face> faces;
	faces.push_back( Face( 0, 1, 2 ) );
	
	std::vector<TextureCoordinate> texCoords;
	texCoords.push_back( TextureCoordinate( 0.0, 0.0) );
	texCoords.push_back( TextureCoordinate( 1.0, 0.0) );
	texCoords.push_back( TextureCoordinate( 1.0, 1.0) );
	
	solidModels.resize(1);
	solidModels.front().set( vertices, faces, texCoords );

	rendererBase->init();
}

void onResize(int width, int height)
{
}

void onKeyDown(unsigned char key, int x, int y )
{
	if( key == 's' ) {
		isIdle ? glutIdleFunc( NULL ) : glutIdleFunc( onIdle );
		isIdle = !isIdle;
	}
	else if( key == 'd' ) {
		distance += 1.0;
	}
	else if( key == 'D' ) {
		distance -= 1.0;
	}

	onDisplay();
}

void onSpecialFunc(int key, int x, int y)
{
	if( key == GLUT_KEY_LEFT ) {
		rendererBase.release();
		rendererBase.reset( new PolygonRendererTest(width, height));
	}
	else if( key == GLUT_KEY_RIGHT ) {
		rendererBase.release();
		rendererBase.reset( new DepthRendererTest(width, height));
	}
	else if( key == GLUT_KEY_UP ) {
		rendererBase.release();
		rendererBase.reset( new BillboardRendererTest(width, height));
	}
	else if( key == GLUT_KEY_DOWN) {
		rendererBase.release();
		rendererBase.reset( new BackGroundRendererTest(width, height ));
	}
	rendererBase->init();
	onDisplay();
}

void onMouse(int button, int state, int x, int y)
{
	if( state == GLUT_DOWN ) {
		mButton = button;
		xBegin = x;
		yBegin = y;
	}
}

void onMotion(int x, int y){
	int diffX = x - xBegin;
	int diffY = y - yBegin;
	if ( mButton == GLUT_LEFT_BUTTON ) {
		Camera::get()->cameraX += diffX * 0.001;
		Camera::get()->cameraY += diffY * 0.001;
	}
	else if( mButton == GLUT_MIDDLE_BUTTON) {
		Camera::get()->zoom += diffY * 0.01;
	}
	else if( mButton == GLUT_RIGHT_BUTTON ) {
		Camera::get()->angleX += diffY * 0.001;
		Camera::get()->angleY += diffX * 0.001;
	}
	onDisplay();
}

void main(int argc, char** argv)
{
	rendererBase.reset( new PolygonRendererTest( width, height ) );
	glutInit(&argc, argv);
	onInit();
	glutDisplayFunc(onDisplay);
	glutIdleFunc(onIdle);
	glutKeyboardFunc(onKeyDown);
	glutReshapeFunc(onResize);
	glutSpecialFunc(onSpecialFunc);
	glutMouseFunc(onMouse);
	glutMotionFunc(onMotion);
	glutMainLoop();
}