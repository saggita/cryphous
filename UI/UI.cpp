#define NOMINMAX 

#include <cassert>
#include "../Graphics/GLee.h"
#include "../Graphics/glut.h"
#include "../Graphics/Camera.h"
#include <gl/gl.h>
#include <gl/glu.h>
#pragma warning (disable : 4996)
#include <memory>

#include "../Math/Box.h"
#include "../Math/Vector3d.h"

#include "../Physics/Particle.h"
#include "../Physics/SPHSolver.h"

#include <iostream>

using namespace Crystal::Math;
using namespace Crystal::Physics;
using namespace Crystal::Graphics;

bool isIdle = true;
float distance = 0.0;

const int width = 1024;
const int height = 768;

PhysicsObjectCollection objects;

#include "../Graphics/RenderingPipeline.h"

RenderingPipeline pipeline;

FrameBufferObject* fbo;

bool isRunning = true;

#include "XMLParser.h"
RenderingPipeline::Param graphicsParam;


PhysicsParam physicsParam;
SPHSolver solver;

Camera camera;

#include <fstream>

#include "../Physics/BoundaryCoordinator.h"
#include "../Physics/Coordinator.h"

#include "../Physics/RigidCoordinator.h"

ExternalForceCoordinator* control = nullptr;

CoordinatorVector createCoordinators( const Box& box )
{
	BoundaryCoordinator* boundary = new BoundaryCoordinator( box );

	CoordinatorVector coordinators;
	coordinators.push_back( boundary );

	//RigidCoordinator* rigid = new RigidCoordinator;
	//coordinators.push_back( rigid );


	ExternalForceCoordinator* external = new ExternalForceCoordinator( physicsParam.externalForce );
	coordinators.push_back( external );

	if( control == nullptr ) {
		control = external;
	}

	coordinators.push_back( new EulerIntegrator() );
	return coordinators;
}

PhysicsObject* createPhysicsObject( const Particle::Constant& constant, const std::vector<Vector3d>& points, const CoordinatorVector& coordinators )
{
	ParticleVector particles;
	for( const Vector3d& point: points ) {
		Particle particle( constant, point );	
		particles.push_back( new Particle( particle ) );
	}

	return new PhysicsObject( particles, coordinators );
}


void refreshSimulation()
{
	control = nullptr;

	Particle::Constant constant;

	physicsParam = XMLParser::parsePhysicsParam( "../param.xml" );

	constant.pressureCoe = physicsParam.pressureCoe;
	constant.viscosityCoe = physicsParam.viscosityCoe;

	solver.init();

	objects.clear();
	
	constant.diameter = physicsParam.particleDiameter;
	constant.restDensity = physicsParam.density;
	
	const float radius = constant.diameter * 0.5f;
	const Box bb = physicsParam.boundaryBox.getInnerOffset( radius );
	
	for( const Box& box : physicsParam.boxes ) {
		const Box& innerBox = box.getInnerOffset( radius );
		const std::vector<Vector3d>& points = innerBox.createPoints( physicsParam.particleDiameter );
		objects.push_back( createPhysicsObject( constant, points, createCoordinators( bb ) ) );
	}

	for( const Sphere& sphere : physicsParam.spheres ) {
		std::vector<Vector3d> points = sphere.createPoints( physicsParam.particleDiameter );
		objects.push_back( createPhysicsObject( constant, points, createCoordinators( bb ) ) );
	}
	
	std::cout << "Particles = " << objects.getParticles().size() << std::endl;
}

void refreshGraphics()
{
	graphicsParam = XMLParser::parseGraphicsParam( "../param.xml" );
}

void proceedSimulation()
{
	if( isRunning ) {
		solver.simulate( objects, physicsParam.getEffectLength(), physicsParam.timeStep );
	}
}

float toRed( const float densityRatio )
{
	if( densityRatio < 0.8f ) {
		return 0.0f;
	}
	else if( densityRatio < 1.0f ) {
		return ( densityRatio - 0.8f ) * 5.0f;
	}
	else {
		return 1.0f;
	}
}

float toGreen( const float densityRatio )
{
	if( densityRatio < 0.8f ) {
		return 0.0f;
	}
	else if( densityRatio < 1.0f ) {
		return ( densityRatio - 0.8f ) * 5.0f;
	}
	else if( densityRatio < 1.2f ) {
		return ( 1.2f - densityRatio ) * 5.0f;
	}
	else {
		return 0.0f;
	}
}

float toBlue( const float densityRatio )
{
	if( densityRatio < 1.0f ) {
		return 1.0f;
	}
	else if( densityRatio < 1.2f ) {
		return ( 1.2f - densityRatio ) * 5.0f;
	}
	else {
		return 0.0f;
	}
}

Color toColor( const Vector3d vector )
{
	return Color( ::fabs( vector.getX() ), ::fabs( vector.getY() ), ::fabs( vector.getZ() ), 1.0f );
}

void onDisplay()
{
	proceedSimulation();

	std::vector< float > positions;
	std::vector< float > colors;

	const ParticleVector& particles = objects.getParticles();
	
	for( Crystal::Physics::Particle* particle : particles ) {
		positions.push_back( particle->getCenter().getX() );
		positions.push_back( particle->getCenter().getY() );
		positions.push_back( particle->getCenter().getZ() );
		//const float density = particle->getDensityRatio() - 1.0f;
		//const float val = particle->getVelocity().getLength();
		//colors.push_back( toRed( val ) );
		//colors.push_back( toGreen( val ) );
		//colors.push_back( toBlue( val ) );
		//colors.push_back( 1.0f );
		Color color = toColor( particle->getVelocity() );
		colors.push_back( color.getRed() );
		colors.push_back( color.getGreen() );
		colors.push_back( color.getBlue() );
		colors.push_back( color.getAlpha() );
	}

	pipeline.render( width, height, positions, colors, &camera, graphicsParam );

	glutSwapBuffers();
}

void onIdle()
{
	glutPostRedisplay();
}

void onInit()
{
	glutInitWindowPosition(0,0);
	glutInitWindowSize( width, height );
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
	
	glutCreateWindow("Crystal Physics");

	camera.zoom = -0.1f;

	fbo = new FrameBufferObject( width, height );

	pipeline.build( width, height );

	refreshSimulation();
	refreshGraphics();
}

void onResize(int width, int height)
{
}

void viewReset(int id)
{
	camera.init();
}

void dumpForce()
{
	Vector3d force = control->getForce();
	std::cout
		<< "external force = "
		<< " x = " << force.getX()
		<< " y = " << force.getY()
		<< " z = " << force.getZ()
		<< std::endl; 
}

void dumpAlpha()
{
	std::cout << "alpha = " << graphicsParam.alpha << std::endl;
}

void dumpFilterRadius()
{
	std::cout << "filter radius = " << graphicsParam.filterRadius << std::endl;
}

void dumpPointSize()
{
	std::cout << "point size = " << graphicsParam.pointSize << std::endl;
}

void onKey(unsigned char key, int x, int y )
{
	if( key == 'd' ) {
		camera.zoom += 0.01f;		
	}
	else if( key == 'D' ) {
		camera.zoom -= 0.01f;
	}
	else if( key == 'r' ) {
		refreshSimulation();
	}
	else if ( key == 'g' ) {
		refreshGraphics();
	}
	else if( key == 'p' ) {
		graphicsParam.pointSize += 1.0f;
		dumpPointSize();
	}
	else if( key == 'P' ) {
		graphicsParam.pointSize -= 1.0f;
		dumpPointSize();
	}
	/*else if( key == 'b' ) {
		pipeline.build( screenSize.getWidth(), screenSize.getHeight() );
	}*/
	else if( key == 'a' ) {
		graphicsParam.alpha += 0.1f;
		dumpAlpha();
	}
	else if( key == 'A') {
		graphicsParam.alpha -= 0.1f;
		dumpAlpha();
	}
	else if( key == 's' ) {
		isRunning = !isRunning;
	}
	else if( key == 'x' ) {
		control->addForce( 1.0f * Vector3d::UnitX() );
		dumpForce();
	}
	else if( key == 'X' ) {
		control->addForce( -1.0f * Vector3d::UnitX() );
		dumpForce();
	}
	else if( key == 'y' ) {
		control->addForce( 1.0f * Vector3d::UnitY() );
		dumpForce();
	}
	else if( key == 'Y' ) {
		control->addForce( -1.0f * Vector3d::UnitY() );
		dumpForce();
	}
	else if( key == 'z' ) {
		control->addForce( 1.0f * Vector3d::UnitZ() );
		dumpForce();
	}
	else if( key == 'Z' ) {
		control->addForce( -1.0f * Vector3d::UnitZ() );
		dumpForce();
	}
	else if( key == 'f' ) {
		++graphicsParam.filterRadius;
		dumpFilterRadius();
	}
	else if( key == 'F' ) {
		--graphicsParam.filterRadius;
		dumpFilterRadius();
	}
}

void onSpecialKey(int key , int x , int y)
{
	switch( key ) {
	case GLUT_KEY_F1 :
		pipeline.selectedTexture = pipeline.getPointSpriteTexture();
		onDisplay();
		break;
	case GLUT_KEY_F2 :
		pipeline.selectedTexture = pipeline.getDepthTexture();
		onDisplay();
		break;
	case GLUT_KEY_F3 :
		pipeline.selectedTexture= pipeline.getDepthSmoothingTexture();
		onDisplay();
		break;
	case GLUT_KEY_F4:
		pipeline.selectedTexture = pipeline.getThicknessTexture();
		onDisplay();
		break;
	case GLUT_KEY_F5:
		pipeline.selectedTexture = pipeline.getThicknessSmoothingTexture();
		onDisplay();
		break;
	case GLUT_KEY_F6:
		pipeline.selectedTexture = pipeline.getNormalTexture();
		onDisplay();
		break;
	case GLUT_KEY_F7:
		pipeline.selectedTexture = pipeline.getSceneTexture();
		onDisplay();
		break;
	case GLUT_KEY_F8:
		pipeline.selectedTexture = pipeline.getFluidTexture();
		onDisplay();
		break;
	case GLUT_KEY_RIGHT:
		camera.cameraX += 0.01f;
		break;
	case GLUT_KEY_LEFT:
		camera.cameraX -= 0.01f;
		break;
	case GLUT_KEY_UP:
		camera.cameraY += 0.01f;
		break;
	case GLUT_KEY_DOWN:
		camera.cameraY -= 0.01f;
		break;
	default:
		break;
	}
}

void dumpUsage()
{
	std::cout << "F1: Point Sprite" << std::endl;
	std::cout << "F2: Depth " << std::endl;
	std::cout << "F3: Depth Smoothing" << std::endl;
	std::cout << "F4: Thickness" << std::endl;
	std::cout << "F5: Thichness Smoothing" << std::endl;
	std::cout << "F6: Normal" << std::endl;
	std::cout << "F7: Scene" << std::endl;
	std::cout << "F8: Fluid" << std::endl;

	std::cout << "r : reset simulation" << std::endl;
	std::cout << "s : stop / start simulation" << std::endl;
	std::cout << "x : increase external force x" << std::endl;
	std::cout << "X : decrease external force y" << std::endl;
	std::cout << "y : add external force y" << std::endl;
	std::cout << "Y : decrease external foroce y" << std::endl;
	std::cout << "z : add external force z" << std::endl;
	std::cout << "Z : decrease external force z" << std::endl;

	std::cout<< " g : reset graphics" << std::endl;
	std::cout << "arrow key : camera move" << std::endl;
	std::cout << "d : camera zoom" << std::endl;
	std::cout << "D : camera out" << std::endl;
	std::cout << "p : increase point size" << std::endl;
	std::cout << "P : decrease point size" << std::endl;
	std::cout << "a : increase alpha" << std::endl;
	std::cout << "A : dcrease alpha" << std::endl;
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	onInit();
	glutDisplayFunc(onDisplay);
	glutReshapeFunc(onResize);
	glutIdleFunc(onIdle);
	glutKeyboardFunc(onKey);
	glutSpecialFunc(onSpecialKey);

	dumpUsage();

	glutMainLoop();
}