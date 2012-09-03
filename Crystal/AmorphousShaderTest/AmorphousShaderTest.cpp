#include "StdAfx.h"
#include <cassert>
#include "../AmorphousShader/GLSLUtility.h"
#include <glut.h>
#include <gl/gl.h>
#include <gl/glu.h>

#include "../CrystalPhysics/PhysicsObjectFactory.h"
#include "../CrystalPhysics/Simulation.h"

using namespace Crystal::Geom;
using namespace Crystal::Physics;
using namespace Crystal::Shader;

bool isIdle = true;
int mButton;
int xBegin;
int yBegin;
float distance = 0.0;

const int width = 756;
const int height = 756;

Crystal::Shader::PBFR* renderer;
Crystal::Shader::PBFRSetting setting;
Crystal::Shader::VisualParticleVector visualParticles;
Crystal::Physics::PhysicsObjectFactory factory;
Crystal::Physics::Simulation simulation;
Crystal::Physics::SimulationSetting ssetting;

void onDisplay()
{
	renderer->render();

	glutSwapBuffers();

	assert( GLSLUtility::hasNoError() );
}

void onIdle()
{
	simulation.simulate( &factory, ssetting );
	const ParticleVector& particles = factory.getOrderedParticles();
	for( size_t i = 0; i < particles.size(); ++i ) {
		visualParticles[i].center = particles[i]->center;
		visualParticles[i].normal = particles[i]->normal.getNormalized();
		visualParticles[i].alpha = particles[i]->density / 2000.0f;
	}
	renderer->setVisualParticles(visualParticles);

	printf("visual particles = %d\n", visualParticles.size() );  

	//onDisplay();
	glutPostRedisplay();
}

void onInit()
{
	glutInitWindowPosition(0,0);
	glutInitWindowSize(width, height);
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );

	glutCreateWindow("CrystalRendererTest");

	Camera::get()->zoom = -0.1f;

	std::vector<Vector3d> points;
	for( float x = -4.0; x < 4.0; x+= 0.1 ) {
		for( float y = 0.0; y < 1.0; y += 0.1 ) {
			for( float z = -4.0; z < 4.0; z += 0.1 ) {
				points.push_back( Vector3d(x, y, z ) );
			}
		}
	}
	//points.push_back( Vector3d(0.0f, 0.0f, 0.0f) );
	PhysicsObjectCondition condition( points, 1000.0, 20000.0, 100.0, PhysicsObjectCondition::Fluid );

	ssetting.boundaryBox = Box( Vector3d( -4.0, 0.0, -4.0), Vector3d( 4.0, 10.0, 4.0 ) );
	factory.createPhysicsObject( condition, ssetting);
	
	visualParticles.resize( points.size() );

	setting.distribute = 0.20;
	setting.pointSize = 200.0;
	setting.pointAlpha = 0.5;
	setting.repeatLevel = 20;

	renderer->init();
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
	renderer = new PBFR(width, height, setting);
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
	delete renderer;
}