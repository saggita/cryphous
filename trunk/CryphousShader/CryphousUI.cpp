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

#include "Bitmap.h"

#include "OnScreenRenderer.h"
#include "PointSpriteRenderer.h"
#include "VisualParticle.h"
#include "DepthRenderer.h"
#include "DepthSmoothingRenderer.h"
#include "ScreenSpaceFluidRenderer.h"
#include "ThicknessRenderer.h"
#include "SplashRenderer.h"

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

float pressure = 200000.0f;
float viscosity = 200.0f;

SimulationSetting setting;
PhysicsObjectFactory factory;
Simulation simulation;

PointSpriteRenderer pointSpriteRenderer(width, height, pointSize, alpha);
DepthRenderer depthRenderer( width, height, pointSize);	
DepthSmoothingRenderer depthSmoothingRenderer( width, height);
ThicknessRenderer thicknessRenderer( width, height, pointSize, alpha);
ScreenSpaceFluidRenderer screenSpaceFluidRenderer( width, height);
OnScreenRenderer onScreenRenderer(width, height);
DepthSmoothingRenderer thicknessSmoothingRenderer(width, height);
SplashRenderer splashRenderer( width, height, pointSize, alpha);

VisualParticleCollection collection;


FrameBufferObject* fbo;

TextureObject* selectedTexture;

GLUI_RadioGroup * renderingGroup;

int mainWindow;

std::vector<Box> fluidBoundary(2);//Vector3d( 0.0, 0.5, -19.5), Vector3d( 19.5, 5.5, 19.5) );

Bitmap bitmap("../Shaders/caustic2.bmp");//("s_cloud2.bmp");//("Test.bmp");

bool isRunning = true;
std::vector<int> isSphere(2, 0);
std::vector<float> radius(2, 5.0);

std::vector<PhysicsObjectCondition> conditions;

void refreshSimulation(int id)
{
	factory.init();
	simulation.init();
	conditions.clear();

	for( int i = 0; i < 1; ++i ) {
		std::vector<Vector3d> points;
		for( float x = fluidBoundary[i].minX; x <= fluidBoundary[i].maxX; x+=0.5 ) {
			for( float y = fluidBoundary[i].minY; y <= fluidBoundary[i].maxY; y+= 0.5 ) {
				for( float z = fluidBoundary[i].minZ; z <= fluidBoundary[i].maxZ; z+= 0.5 ) {
					if( !isSphere[i] ) {
						points.push_back( Vector3d( x, y, z ) );
					}
					else {
						const Vector3d& center = fluidBoundary[i].getCenter();
						if( center.getDistanceSquared(Vector3d( x, y, z ) ) < radius[i] * radius[i]){
							points.push_back( Vector3d( x, y, z ) );
						}
					}
				}
			}
		}
		Cryphous::Physics::PhysicsObjectCondition condition1( points, 1000.0f, pressure, viscosity, Cryphous::Physics::PhysicsObjectCondition::Fluid );
		conditions.push_back( condition1 );
	}

	for( const PhysicsObjectCondition& condition: conditions ) {
		factory.createPhysicsObject( condition, setting );
	}
	std::cout << "Particles = " << factory.getParticles().size() << std::endl;
}

void proceedSimulation(int id)
{
	if( !isRunning ) {
		return;
	}
	simulation.simulate( &factory, setting);
	VisualParticleList visualParticles;
	for( Cryphous::Physics::Particle* particle : factory.getParticles() ) {
		visualParticles.push_back( VisualParticle( Vector3d(particle->center.x, particle->center.y, particle->center.z), particle->density ) );
	}
	collection.set( visualParticles );
	depthRenderer.setVisualParticles( &collection );
	thicknessRenderer.setVisualParticles( &collection );
	pointSpriteRenderer.setVisualParticles( &collection );
	splashRenderer.setVisualParticles( &collection );
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

	TextureObject bmpTexture( bitmap.colors, bitmap.sizeX, bitmap.sizeY);

	screenSpaceFluidRenderer.setThicknessTexture( &(thicknessSmoothingRenderer.getFrameBufferObject()->getTextureObject() ) );
	screenSpaceFluidRenderer.setDepthSmoothingTexture( &(depthSmoothingRenderer.getFrameBufferObject()->getTextureObject() ) );
	screenSpaceFluidRenderer.setBackgroundTexture( &bmpTexture );
	screenSpaceFluidRenderer.render();

	splashRenderer.render();

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

	fbo = new FrameBufferObject(width, height, false);

	pointSpriteRenderer.init();
	depthRenderer.init();
	depthSmoothingRenderer.init();
	thicknessRenderer.init();
	thicknessSmoothingRenderer.init();
	screenSpaceFluidRenderer.init();
	splashRenderer.init();
	onScreenRenderer.init();
	selectedTexture = &(pointSpriteRenderer.getFrameBufferObject()->getTextureObject());

	fluidBoundary[0] = Box(Vector3d( 0.0, 0.5, -19.5), Vector3d( 19.5, 5.5, 0.5) );
	fluidBoundary[1] = Box(Vector3d( -19.5, 0.5, 0.5), Vector3d( 0.0, 5.5, 19.5) );

	refreshSimulation(0);
}

void onResize(int width, int height)
{
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
	else if( selectedId == 5 ) {
		selectedTexture = &(splashRenderer.getFrameBufferObject()->getTextureObject() );
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

void stopSimulation(int)
{
	isRunning = !isRunning;
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
	for( int i = 0; i < 1; ++i ) {
		glui->add_spinner_to_panel( objectBoundary, "MinX", GLUI_SPINNER_FLOAT, &fluidBoundary[i].minX );
		glui->add_spinner_to_panel( objectBoundary, "MaxX", GLUI_SPINNER_FLOAT, &fluidBoundary[i].maxX );
		glui->add_spinner_to_panel( objectBoundary, "MinY", GLUI_SPINNER_FLOAT, &fluidBoundary[i].minY );
		glui->add_spinner_to_panel( objectBoundary, "MaxY", GLUI_SPINNER_FLOAT, &fluidBoundary[i].maxY );
		glui->add_spinner_to_panel( objectBoundary, "MinZ", GLUI_SPINNER_FLOAT, &fluidBoundary[i].minZ );
		glui->add_spinner_to_panel( objectBoundary, "MaxZ", GLUI_SPINNER_FLOAT, &fluidBoundary[i].maxZ );
		glui->add_checkbox_to_panel( objectBoundary, "Sphere", &isSphere[i] );
		glui->add_spinner_to_panel( objectBoundary, "Radius", GLUI_SPINNER_FLOAT, &radius[i] );
	}

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
	glui->add_button_to_panel( simulationRollout, "Stop", 4, stopSimulation );

	renderingGroup = glui->add_radiogroup(0, -1, changeRenderer);
	glui->add_radiobutton_to_group( renderingGroup, "PointSprite" );
	glui->add_radiobutton_to_group( renderingGroup, "Depth" );
	glui->add_radiobutton_to_group( renderingGroup, "DepthSmoothing");
	glui->add_radiobutton_to_group( renderingGroup, "Thickness" );
	glui->add_radiobutton_to_group( renderingGroup, "ScreenSpaceFluid");
	glui->add_radiobutton_to_group( renderingGroup, "Splash");

	glui->set_main_gfx_window( mainWindow );
	GLUI_Master.set_glutIdleFunc( onIdle );
}

void main(int argc, char** argv)
{
	refreshSimulation(0);

	glutInit(&argc, argv);
	onInit();
	glutDisplayFunc(onDisplay);
	glutReshapeFunc(onResize);
	glutMouseFunc(onMouse);
	glutMotionFunc(onMotion);

	createControl();

	glutMainLoop();
}