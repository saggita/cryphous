#include "CryphousShader.h"
#include <cassert>
#include "GLSLUtility.h"
#include <glut.h>
#include <gl/gl.h>
#include <gl/glu.h>
#pragma warning (disable : 4996)
#include <gl/glui.h>
#include <memory>

#include "../CryphousGeometry/Vector3d.h"

#include "../CryphousPhysics/SimulationSetting.h"
#include "../CryphousPhysics/PhysicsObjectFactory.h"
#include "../CryphousPhysics/Simulation.h"

#include "OnScreenRenderer.h"
#include "PointSpriteRenderer.h"
#include "VisualParticle.h"
#include "DepthRenderer.h"
#include "DepthSmoothingRenderer.h"
#include "ScreenSpaceFluidRenderer.h"
#include "ThicknessRenderer.h"

#include <iostream>

using namespace Cryphous::Geometry;
using namespace Cryphous::Physics;
using namespace Cryphous::Shader;

bool isIdle = true;
int mButton;
int xBegin;
int yBegin;
float distance = 0.0;

const int width = 864;//512;
const int height = 486;//512;

float pointSize = 500.0f;
float alpha = 0.2f;

float pressure = 100000.0f;
float viscosity = 200.0f;

SimulationSetting setting;
PhysicsObjectFactory factory;
Simulation simulation;

Cryphous::Shader::PointSpriteRenderer pointSpriteRenderer(width, height, pointSize, alpha);
Cryphous::Shader::DepthRenderer depthRenderer( width, height, pointSize);	
Cryphous::Shader::DepthSmoothingRenderer depthSmoothingRenderer( width, height);
Cryphous::Shader::ThicknessRenderer thicknessRenderer( width, height, pointSize, alpha);
Cryphous::Shader::ScreenSpaceFluidRenderer screenSpaceFluidRenderer( width, height);
Cryphous::Shader::OnScreenRenderer onScreenRenderer(width, height);
Cryphous::Shader::DepthSmoothingRenderer thicknessSmoothingRenderer(width, height);

TextureObject* selectedTexture;

GLUI_RadioGroup * renderingGroup;

int mainWindow;

Box fluidBoundary(Vector3d( -10.5, 0.5, 0.5), Vector3d( 10.0, 5.5, 19.5) );

void refreshSimulation(int id)
{
	factory.init();
	simulation.init();

	std::vector<Vector3d> points;
	for( float x = fluidBoundary.minX; x <= fluidBoundary.maxX; x+=0.5 ) {
		for( float y = fluidBoundary.minY; y <= fluidBoundary.maxY; y+= 0.5 ) {
			for( float z = fluidBoundary.minZ; z <= fluidBoundary.maxZ; z+= 0.5 ) {
				points.push_back( Vector3d( x, y, z ) );
			}
		}
	}
	Cryphous::Physics::PhysicsObjectCondition condition1( points, 1000.0f, pressure, viscosity, Cryphous::Physics::PhysicsObjectCondition::Fluid );
	factory.createPhysicsObject( condition1, setting );

	std::cout << "Particles = " << factory.getParticles().size() << std::endl;
}

void proceedSimulation(int id)
{
	simulation.simulate( &factory, setting);
	VisualParticleList visualParticles;
	for( Cryphous::Physics::Particle* particle : factory.getParticles() ) {
		visualParticles.push_back( VisualParticle( Vector3d(particle->center.x, particle->center.y, particle->center.z) ) );
	}
	depthRenderer.setVisualParticles( visualParticles );
	thicknessRenderer.setVisualParticles( visualParticles );
	pointSpriteRenderer.setVisualParticles( visualParticles );
}


void onDisplay()
{
	proceedSimulation(0);

	pointSpriteRenderer.render();
	depthRenderer.render();
	depthSmoothingRenderer.setDepthTexture( &(depthRenderer.getFrameBufferObject()->getTextureObject() ) );
	depthSmoothingRenderer.render();
	
	thicknessRenderer.render();
	thicknessSmoothingRenderer.setDepthTexture( &(thicknessRenderer.getFrameBufferObject()->getTextureObject() ) );
	thicknessSmoothingRenderer.render();

	screenSpaceFluidRenderer.setThicknessTexture( &(thicknessSmoothingRenderer.getFrameBufferObject()->getTextureObject() ) );
	screenSpaceFluidRenderer.setDepthSmoothingTexture( &(depthSmoothingRenderer.getFrameBufferObject()->getTextureObject() ) );
	screenSpaceFluidRenderer.render();


	onScreenRenderer.setTexture( selectedTexture );
	onScreenRenderer.render();

	glutSwapBuffers();

	assert( GLSLUtility::hasNoError() );
}

void startSimulation(int id)
{
}

void onIdle()
{
	glutSetWindow(mainWindow);
	onScreenRenderer.idle();
	glutPostRedisplay();
}

void onInit()
{
	glutInitWindowPosition(0,0);
	glutInitWindowSize(width, height);
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );

	mainWindow = glutCreateWindow("CryphousRendererTest");

	Camera::get()->zoom = -0.1f;

	pointSpriteRenderer.init();
	depthRenderer.init();
	depthSmoothingRenderer.init();
	thicknessRenderer.init();
	thicknessSmoothingRenderer.init();
	screenSpaceFluidRenderer.init();
	onScreenRenderer.init();
	selectedTexture = &(pointSpriteRenderer.getFrameBufferObject()->getTextureObject());
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

void viewReset(int id)
{
	Camera::get()->init();
}

void changeRenderer(int id)
{	
	int selectedId = renderingGroup->get_int_val();

	if( selectedId == 0 ) {
		selectedTexture = &(pointSpriteRenderer.getFrameBufferObject()->getTextureObject() );
	}
	else if( selectedId == 1 ) {
		selectedTexture = &(depthRenderer.getFrameBufferObject()->getTextureObject() );
	}
	else if( selectedId == 2 ) {
		selectedTexture = &(depthSmoothingRenderer.getFrameBufferObject()->getTextureObject() );
	}
	else if( selectedId == 3) {
		selectedTexture =&(thicknessSmoothingRenderer.getFrameBufferObject()->getTextureObject() );
	}
	else if( selectedId == 4 ) {
		selectedTexture = &(screenSpaceFluidRenderer.getFrameBufferObject()->getTextureObject() );
	}
	else {
		assert( false );
	}
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

void createControl()
{
	GLUI *glui = GLUI_Master.create_glui( "GLUI" );
	
	GLUI_Rollout *graphicsRollout = glui->add_rollout("Graphics Setting");
	glui->add_checkbox_to_panel( graphicsRollout, "DrawBoundary");
	GLUI_Spinner *spinner = glui->add_spinner_to_panel( graphicsRollout, "PointSize" , GLUI_SPINNER_FLOAT, &pointSize );
	spinner->set_int_limits( 1.0f, 1000.0f );
	GLUI_Spinner *alphaSpinner = glui->add_spinner_to_panel( graphicsRollout, "PointAlpha", GLUI_SPINNER_FLOAT, &alpha );
	alphaSpinner->set_float_limits( 0.0f, 1.0f );

	GLUI_Rollout* simulationSettingRollout = glui->add_rollout("SimulationSetting");
	glui->add_spinner_to_panel( simulationSettingRollout, "X", GLUI_SPINNER_FLOAT, &setting.externalForce.x );
	glui->add_spinner_to_panel( simulationSettingRollout, "Y", GLUI_SPINNER_FLOAT, &setting.externalForce.y );
	glui->add_spinner_to_panel( simulationSettingRollout, "Z", GLUI_SPINNER_FLOAT, &setting.externalForce.z );
	glui->add_spinner_to_panel( simulationSettingRollout, "Press", GLUI_SPINNER_FLOAT, &pressure );
	glui->add_spinner_to_panel( simulationSettingRollout, "Visc", GLUI_SPINNER_FLOAT, &viscosity );


	GLUI_Listbox* listBox = glui->add_listbox_to_panel( simulationSettingRollout, "Type" );
	listBox->add_item(0, "Fluid");
	listBox->add_item(1, "Rigid");
	listBox->add_item(2, "Obstacle");

	GLUI_Rollout* objectBoundary = glui->add_rollout("ObjectBoundary");
	glui->add_spinner_to_panel( objectBoundary, "MinX", GLUI_SPINNER_FLOAT, &fluidBoundary.minX );
	glui->add_spinner_to_panel( objectBoundary, "MaxX", GLUI_SPINNER_FLOAT, &fluidBoundary.maxX );
	glui->add_spinner_to_panel( objectBoundary, "MinY", GLUI_SPINNER_FLOAT, &fluidBoundary.minY );
	glui->add_spinner_to_panel( objectBoundary, "MaxY", GLUI_SPINNER_FLOAT, &fluidBoundary.maxY );
	glui->add_spinner_to_panel( objectBoundary, "MinZ", GLUI_SPINNER_FLOAT, &fluidBoundary.minZ );
	glui->add_spinner_to_panel( objectBoundary, "MaxZ", GLUI_SPINNER_FLOAT, &fluidBoundary.maxZ );

	GLUI_Spinner *boundaryMinXSpinner = glui->add_spinner_to_panel( simulationSettingRollout, "MinX", GLUI_SPINNER_FLOAT, &setting.boundaryBox.minX );
	GLUI_Spinner *boundaryMaxXSpinner = glui->add_spinner_to_panel( simulationSettingRollout, "MaxX", GLUI_SPINNER_FLOAT, &setting.boundaryBox.maxX );
	GLUI_Spinner *boundaryMinYSpinner = glui->add_spinner_to_panel( simulationSettingRollout, "MinY", GLUI_SPINNER_FLOAT, &setting.boundaryBox.minY );
	GLUI_Spinner *boundaryMaxYSpinner = glui->add_spinner_to_panel( simulationSettingRollout, "MaxY", GLUI_SPINNER_FLOAT, &setting.boundaryBox.maxY );
	GLUI_Spinner *boundaryMinZSpinner = glui->add_spinner_to_panel( simulationSettingRollout, "MinZ", GLUI_SPINNER_FLOAT, &setting.boundaryBox.minZ );
	GLUI_Spinner *boundaryMaxZSpinner = glui->add_spinner_to_panel( simulationSettingRollout, "MaxZ", GLUI_SPINNER_FLOAT, &setting.boundaryBox.maxZ );

	GLUI_Rollout *simulationRollout = glui->add_rollout("Simulation");
	glui->add_button_to_panel( simulationRollout, "ViewReset", 3, viewReset);
	glui->add_button_to_panel( simulationRollout, "Refresh", 2, refreshSimulation );
	glui->add_button_to_panel( simulationRollout, "Proceed", 1, proceedSimulation);

	renderingGroup = glui->add_radiogroup(0, -1, changeRenderer);
	glui->add_radiobutton_to_group( renderingGroup, "PointSprite" );
	glui->add_radiobutton_to_group( renderingGroup, "Depth" );
	glui->add_radiobutton_to_group( renderingGroup, "DepthSmoothing");
	glui->add_radiobutton_to_group( renderingGroup, "Thickness" );
	glui->add_radiobutton_to_group( renderingGroup, "ScreenSpaceFluid");

	glui->set_main_gfx_window( mainWindow );
	GLUI_Master.set_glutIdleFunc( onIdle );
}

void main(int argc, char** argv)
{
	refreshSimulation(0);

	glutInit(&argc, argv);
	onInit();
	glutDisplayFunc(onDisplay);
	//glutIdleFunc(onIdle);
	glutKeyboardFunc(onKeyDown);
	glutReshapeFunc(onResize);
	glutMouseFunc(onMouse);
	glutMotionFunc(onMotion);

	createControl();

	glutMainLoop();
}