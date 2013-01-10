#include "CrystalShader.h"
#include <cassert>
#include "GLSLUtility.h"
#include <glut.h>
#include <gl/gl.h>
#include <gl/glu.h>
#pragma warning (disable : 4996)
#include <gl/glui.h>
#include <memory>

#include "../CrystalGeom/Vector3d.h"

#include "OnScreenRenderer.h"
#include "PointSpriteRenderer.h"
#include "VisualParticle.h"
#include "DepthRenderer.h"
#include "DepthSmoothingRenderer.h"
#include "ScreenSpaceFluidRenderer.h"

using namespace Crystal::Shader;

bool isIdle = true;
int mButton;
int xBegin;
int yBegin;
float distance = 0.0;

const int width = 512;
const int height = 512;

const float size = 50.0f;
const float alpha = 1.0f;

Crystal::Shader::VisualParticleList visualParticles;
Crystal::Shader::PointSpriteRenderer* pointSpriteRenderer;
Crystal::Shader::DepthRenderer* depthRenderer;
Crystal::Shader::DepthSmoothingRenderer* depthSmoothingRenderer;
Crystal::Shader::ScreenSpaceFluidRenderer* screenSpaceFluidRenderer;
Crystal::Shader::OnScreenRenderer* onScreenRenderer;

int mainWindow;

void onDisplay()
{
	onScreenRenderer->render();

	glutSwapBuffers();

	assert( GLSLUtility::hasNoError() );
}

void onIdle()
{
	onScreenRenderer->idle();
	glutPostRedisplay();
}

void onInit()
{
	glutInitWindowPosition(0,0);
	glutInitWindowSize(width, height);
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );

	mainWindow = glutCreateWindow("CrystalRendererTest");

	Camera::get()->zoom = -0.1f;

	onScreenRenderer->init();
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
		onScreenRenderer->setOffScreenRenderer( pointSpriteRenderer );
	}
	else if( key == GLUT_KEY_RIGHT ) {
		onScreenRenderer->setOffScreenRenderer( depthRenderer );
	}
	else if( key == GLUT_KEY_UP ) {
		onScreenRenderer->setOffScreenRenderer( depthSmoothingRenderer );
	}
	else if( key == GLUT_KEY_DOWN) {
		onScreenRenderer->setOffScreenRenderer( screenSpaceFluidRenderer );
	}
	onScreenRenderer->init();
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
	onScreenRenderer = new OnScreenRenderer(width, height);

	visualParticles.push_back( VisualParticle() );
	visualParticles.push_back( VisualParticle( Crystal::Geom::Vector3d( 0.1f, 0.0f, -5.0f ), 1.0 ) );

	for( size_t i = 0; i < 10; ++i ) {
		visualParticles.push_back( VisualParticle( Crystal::Geom::Vector3d( 0.01f * i, 0.0f, -1.0f ), 1.0 ) );
	}
	
	pointSpriteRenderer = new PointSpriteRenderer( width, height, size, alpha);
	pointSpriteRenderer->setVisualParticles( visualParticles );

	depthRenderer = new DepthRenderer( width, height, size);
	depthRenderer->setVisualParticles( visualParticles );

	depthSmoothingRenderer = new DepthSmoothingRenderer( width, height);
	depthSmoothingRenderer->setOffScreenRenderer( depthRenderer );

	screenSpaceFluidRenderer = new ScreenSpaceFluidRenderer( width, height );
	screenSpaceFluidRenderer->setOffScreenRenderer( depthSmoothingRenderer );

	onScreenRenderer->setOffScreenRenderer( screenSpaceFluidRenderer );

	glutInit(&argc, argv);
	onInit();
	glutDisplayFunc(onDisplay);
	//glutIdleFunc(onIdle);
	glutKeyboardFunc(onKeyDown);
	glutReshapeFunc(onResize);
	glutSpecialFunc(onSpecialFunc);
	glutMouseFunc(onMouse);
	glutMotionFunc(onMotion);

	GLUI *glui = GLUI_Master.create_glui( "GLUI" );
	glui->add_checkbox("TestCheckBox");
	GLUI_Spinner *spinner = glui->add_spinner( "TestSpinner" , GLUI_SPINNER_INT );
	spinner->set_int_limits( 3, 60 );
	glui->set_main_gfx_window( mainWindow );
	GLUI_Master.set_glutIdleFunc( onIdle );

	glutMainLoop();
}