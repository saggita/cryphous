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

#include "../CrystalPhysics/SimulationSetting.h"
#include "../CrystalPhysics/PhysicsObjectFactory.h"
#include "../CrystalPhysics/Simulation.h"

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

Crystal::Physics::SimulationSetting setting;
Crystal::Physics::PhysicsObjectFactory factory;
Crystal::Physics::Simulation simulation;

Crystal::Shader::VisualParticleList visualParticles;
Crystal::Shader::PointSpriteRenderer* pointSpriteRenderer;
Crystal::Shader::DepthRenderer* depthRenderer;
Crystal::Shader::DepthSmoothingRenderer* depthSmoothingRenderer;
Crystal::Shader::ScreenSpaceFluidRenderer* screenSpaceFluidRenderer;
Crystal::Shader::OnScreenRenderer* onScreenRenderer;

bool isUnderSimulation = false;

int mainWindow;

void refreshSimulation(int id)
{
	visualParticles.clear();
	factory.init();
	simulation.init();

	std::vector<Crystal::Geom::Vector3d> points;
	points.push_back( Crystal::Geom::Vector3d( 0.0, 0.5, 0.0 ) );
	points.push_back( Crystal::Geom::Vector3d( 0.0, 1.0, 0.0 ) );
	Crystal::Physics::PhysicsObjectCondition condition( points, 1000.0f, 10000.0f, 100.0f, Crystal::Physics::PhysicsObjectCondition::Fluid );
	factory.createPhysicsObject( condition, setting );

}

void proceedSimulation(int id)
{
	simulation.simulate( &factory, setting);
	visualParticles.clear();
	for( Crystal::Physics::Particle* particle : factory.getParticles() ) {
		visualParticles.push_back( VisualParticle( Crystal::Geom::Vector3d(particle->center.x, particle->center.y, particle->center.z), 1.0 ) );
	}
	depthRenderer->setVisualParticles ( visualParticles );
	//onDisplay();
}


void onDisplay()
{
	if( isUnderSimulation ) {
		proceedSimulation(0);
	}
	onScreenRenderer->render();

	glutSwapBuffers();

	assert( GLSLUtility::hasNoError() );
}

void startSimulation(int id)
{
	isUnderSimulation = true;
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
	refreshSimulation(0);

	onScreenRenderer = new OnScreenRenderer(width, height);

	for( Crystal::Physics::Particle* particle : factory.getParticles() ) {
		visualParticles.push_back( VisualParticle( Crystal::Geom::Vector3d(particle->center.x, particle->center.y, particle->center.z), 1.0 ) );
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
	
	GLUI_Rollout *graphicsRollout = glui->add_rollout("Graphics Setting");
	glui->add_checkbox_to_panel( graphicsRollout, "DrawBoundary");
	GLUI_Spinner *spinner = glui->add_spinner_to_panel( graphicsRollout, "PointSize" , GLUI_SPINNER_INT );
	spinner->set_int_limits( 3, 60 );

	GLUI_Rollout* simulationSettingRollout = glui->add_rollout("SimulationSetting");
	glui->add_spinner_to_panel( simulationSettingRollout, "X", GLUI_SPINNER_FLOAT, &setting.externalForce.x );
	glui->add_spinner_to_panel( simulationSettingRollout, "Y", GLUI_SPINNER_FLOAT, &setting.externalForce.y );
	glui->add_spinner_to_panel( simulationSettingRollout, "Z", GLUI_SPINNER_FLOAT, &setting.externalForce.z );

	GLUI_Listbox* listBox = glui->add_listbox_to_panel( simulationSettingRollout, "Type" );
	listBox->add_item(0, "Fluid");
	listBox->add_item(1, "Rigid");
	listBox->add_item(2, "Obstacle");

	GLUI_Spinner *boundaryMinXSpinner = glui->add_spinner_to_panel( simulationSettingRollout, "MinX", GLUI_SPINNER_FLOAT, &setting.boundaryBox.minX );
	GLUI_Spinner *boundaryMaxXSpinner = glui->add_spinner_to_panel( simulationSettingRollout, "MaxX", GLUI_SPINNER_FLOAT, &setting.boundaryBox.maxX );
	GLUI_Spinner *boundaryMinYSpinner = glui->add_spinner_to_panel( simulationSettingRollout, "MinY", GLUI_SPINNER_FLOAT, &setting.boundaryBox.minY );
	GLUI_Spinner *boundaryMaxYSpinner = glui->add_spinner_to_panel( simulationSettingRollout, "MaxY", GLUI_SPINNER_FLOAT, &setting.boundaryBox.maxY );
	GLUI_Spinner *boundaryMinZSpinner = glui->add_spinner_to_panel( simulationSettingRollout, "MinZ", GLUI_SPINNER_FLOAT, &setting.boundaryBox.minZ );
	GLUI_Spinner *boundaryMaxZSpinner = glui->add_spinner_to_panel( simulationSettingRollout, "MaxZ", GLUI_SPINNER_FLOAT, &setting.boundaryBox.maxZ );

	GLUI_Rollout *simulationRollout = glui->add_rollout("Simulation");
	glui->add_button_to_panel( simulationRollout, "ViewReset");
	glui->add_button_to_panel( simulationRollout, "Refresh", 2, refreshSimulation );
	glui->add_button_to_panel( simulationRollout, "Start/Stop", 3, startSimulation );
	glui->add_button_to_panel( simulationRollout, "Proceed", 1, proceedSimulation);


	glui->set_main_gfx_window( mainWindow );
	GLUI_Master.set_glutIdleFunc( onIdle );

	glutMainLoop();
}