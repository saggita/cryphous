#include "CryphousShader.h"
#include <cassert>
#include "GLSLUtility.h"
#include "glut.h"
#include <gl/gl.h>
#include <gl/glu.h>
#pragma warning (disable : 4996)
#include <memory>

#include "VisualParticle.h"

#include "../Math/Box.h"
#include "../Math/Vector3d.h"

#include "../Physics/Particle.h"
#include "../Physics/SPHSolver.h"

#include <iostream>

using namespace Crystal::Math;
using namespace Crystal::Physics;
using namespace Crystal::Shader;

bool isIdle = true;
float distance = 0.0;

class ScreenSize
{
public:
	ScreenSize(unsigned int width, unsigned int height) :
	width( width),
	height( height)
	{
	}

	unsigned int getWidth() const { return width; }

	unsigned int getHeight() const { return height; }

private:
	unsigned int width;
	unsigned int height;
};

ScreenSize screenSize(1024,768);

PhysicsObjectCollection objects;

#include "Renderers.h"

Renderers renderers;

FrameBufferObject* fbo;

bool isRunning = true;

struct Setting
{
public:
	float getEffectLength() const { return particleDiameter * 1.25f; }

public:
	float timeStep;
	float particleDiameter;
	Box boundaryBox;
	Vector3d externalForce;
};

Setting setting;
SPHSolver solver;

#include <fstream>

#include "../Physics/BoundaryCoordinator.h"
#include "../Physics/Coordinator.h"

#include "../Physics/RigidCoordinator.h"

#include "tinyxml2.h"

using namespace tinyxml2;

Vector3d readFromXML(XMLElement* element)
{
	Vector3d vector;
	element->QueryFloatAttribute( "x", &vector.x );
	element->QueryFloatAttribute( "y", &vector.y );
	element->QueryFloatAttribute( "z", &vector.z );
	return vector;
}

struct Sphere
{
	Vector3d center;
	float radius;
};

void readFromXML( float* pressureCoe, float* viscosityCoe, std::vector<Box>& boxes, std::vector<Sphere>& spheres)
{
	XMLDocument doc;
	doc.LoadFile( "../param.xml" );

	XMLElement* minElem = doc.FirstChildElement()->FirstChildElement("boundaryMin");
	Vector3d boundaryMin = readFromXML( minElem );
	XMLElement* maxElem = doc.FirstChildElement()->FirstChildElement("boundaryMax");
	Vector3d boundaryMax = readFromXML( maxElem );
	setting.boundaryBox = Box( boundaryMin, boundaryMax );

	XMLElement* minObjElem = doc.FirstChildElement()->FirstChildElement( "objectMin" );
	XMLElement* maxObjElem = doc.FirstChildElement()->FirstChildElement( "objectMax" );

	while( true ) {
		if( minObjElem == NULL  || maxObjElem == NULL ) {
			break;
		}
		Vector3d min = readFromXML( minObjElem );
		Vector3d max = readFromXML( maxObjElem );
		boxes.push_back( Box( min, max ) );
		minObjElem = minObjElem->NextSiblingElement( "objectMin" );
		maxObjElem = maxObjElem->NextSiblingElement( "objectMax" );
	}

	XMLElement* centerElem = doc.FirstChildElement()->FirstChildElement( "sphereCenter" );
	XMLElement* radiusElem = doc.FirstChildElement()->FirstChildElement( "sphereRadius" );

	while( true ) {
		if( centerElem == NULL || radiusElem == NULL ) {
			break;
		}
		Sphere sphere;
		sphere.center = readFromXML( centerElem );
		radiusElem->QueryFloatAttribute( "v", &sphere.radius );
		spheres.push_back( sphere );
		
		centerElem = centerElem->NextSiblingElement( "sphereCenter" );
		radiusElem = radiusElem->NextSiblingElement( "sphereRadius");
	}

	setting.externalForce = readFromXML( doc.FirstChildElement()->FirstChildElement("externalForce") );
	
	XMLElement* diameterElem = doc.FirstChildElement()->FirstChildElement("particleDiameter");
	diameterElem->QueryFloatAttribute( "v", &setting.particleDiameter );
	XMLElement* timeStepElem = doc.FirstChildElement()->FirstChildElement("timeStep");
	timeStepElem->QueryFloatAttribute( "v", &setting.timeStep );
	XMLElement* pressureCoeElem = doc.FirstChildElement()->FirstChildElement("pressureCoe");
	pressureCoeElem->QueryFloatAttribute( "v", pressureCoe );
	XMLElement* viscCoeElem = doc.FirstChildElement()->FirstChildElement("viscosityCoe");
	viscCoeElem->QueryFloatAttribute( "v", viscosityCoe );
}

std::vector<Vector3d> createPoints(const Sphere& sphere)
{
	std::vector<Vector3d> points;

	const float radius = sphere.radius;

	Box box( sphere.center, sphere.center );
	box.outerOffset( radius );

	for( float x = box.minX; x <= box.maxX; x+= setting.particleDiameter ) {
		for( float y = box.minY; y <= box.maxY; y += setting.particleDiameter ) {
			for( float z = box.minZ; z <= box.maxZ; z += setting.particleDiameter ) {
				const Vector3d pos( x, y, z );
				if( pos.getDistanceSquared( sphere.center ) < radius * radius ) {
					points.push_back( pos );
				}
			}
		}
	}
	return points;
}

std::vector<Vector3d> createPoints(const Box& box)
{
	std::vector<Vector3d> points;
	for( float x = box.minX; x <= box.maxX; x+= setting.particleDiameter ) {
		for( float y = box.minY; y <= box.maxY; y += setting.particleDiameter ) {
			for( float z = box.minZ; z <= box.maxZ; z += setting.particleDiameter ) {
				points.push_back( Vector3d( x, y, z ) );
			}
		}
	}
	return points;
}

CoordinatorVector createCoordinators( const Box& box )
{
	BoundaryCoordinator* boundary = new BoundaryCoordinator( box );

	CoordinatorVector coordinators;
	coordinators.push_back( boundary );

	//RigidCoordinator* rigid = new RigidCoordinator;
	//coordinators.push_back( rigid );

	ExternalForceCoordinator* external = new ExternalForceCoordinator( setting.externalForce );
	coordinators.push_back( external );

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
	Particle::Constant constant;

	std::vector<Box> boxes;
	std::vector<Sphere> spheres;

	readFromXML( &constant.pressureCoe, &constant.viscosityCoe, boxes, spheres );

	solver.init();

	objects.clear();
	
	constant.diameter = setting.particleDiameter;

	constant.restDensity = 1000.0f;
	
	const float radius = constant.diameter * 0.5f;
	const Box bb = setting.boundaryBox.getInnerOffset( radius );
	
	for( const Box& box : boxes ) {
		std::vector<Vector3d> points = createPoints( box );
		objects.push_back( createPhysicsObject( constant, points, createCoordinators( bb ) ) );
	}

	for( const Sphere& sphere : spheres ) {
		std::vector<Vector3d> points = createPoints( sphere );
		objects.push_back( createPhysicsObject( constant, points, createCoordinators( bb ) ) );
	}
	
	std::cout << "Particles = " << objects.getParticles().size() << std::endl;
}

void proceedSimulation(int id)
{
	if( !isRunning ) {
		return;
	}
	solver.simulate( objects, setting.getEffectLength(), setting.timeStep );

	VisualParticleVector visualParticles;

	const ParticleVector& particles = objects.getParticles();
	for( Crystal::Physics::Particle* particle : particles ) {
		VisualParticle vp;
		vp.center = particle->getCenter();
		vp.density = particle->getDensity();
		visualParticles.push_back( vp );
	}
	renderers.setPointSize( 10.0f );
	renderers.setParticles( visualParticles );	
}

void onDisplay()
{
	proceedSimulation(0);

	renderers.render();

	glutSwapBuffers();

	assert( GLSLUtility::hasNoError() );
}

void onIdle()
{
	renderers.onScreenRenderer->idle();
	glutPostRedisplay();
}

void onInit()
{
	glutInitWindowPosition(0,0);
	glutInitWindowSize( screenSize.getWidth(), screenSize.getHeight() );
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
	
	glutCreateWindow("RendererTest");

	Camera::get()->zoom = -0.1f;

	fbo = new FrameBufferObject( screenSize.getWidth(), screenSize.getHeight(), false);

	renderers.create();

	renderers.init( screenSize.getWidth(), screenSize.getHeight());

	refreshSimulation();
}

void onResize(int width, int height)
{
}

void viewReset(int id)
{
	Camera::get()->init();
}

void changeRenderingMode(int selectedId){
	TextureObjectMap& map = renderers.createTextureObjectMap();
	
	renderers.selectedTexture = map[selectedId];
	
	onDisplay();
}

void onKey(unsigned char key, int x, int y )
{
	if( key == 'z' ) {
		Camera::get()->zoom += 0.1f;		
	}
	else if( key == 'd' ) {
		Camera::get()->zoom -= 0.1f;
	}
	else if( key == 'r' ) {
		refreshSimulation();
	}
}

void onSpecialKey(int key , int x , int y)
{
	switch( key ) {
	case GLUT_KEY_F1 :
		changeRenderingMode( 0 );
		break;
	case GLUT_KEY_F2 :
		changeRenderingMode( 1 );
		break;
	case GLUT_KEY_F3 :
		changeRenderingMode( 2 );
		break;
	case GLUT_KEY_F4:
		changeRenderingMode( 3 );
		break;
	case GLUT_KEY_F5:
		changeRenderingMode( 4 );
		break;
	case GLUT_KEY_F6:
		changeRenderingMode( 5 );
		break;
	case GLUT_KEY_RIGHT:
		Camera::get()->cameraX += 0.1f;
		break;
	case GLUT_KEY_LEFT:
		Camera::get()->cameraX -= 0.1f;
		break;
	case GLUT_KEY_UP:
		Camera::get()->cameraY += 0.1f;
		break;
	case GLUT_KEY_DOWN:
		Camera::get()->cameraY -= 0.1f;
		break;
	default:
		break;
	}
}

void stopSimulation(int)
{
	isRunning = !isRunning;
}

void printUsage()
{
	std::cout << "F1: Point Sprite" << std::endl;
	std::cout << "F2: Depth " << std::endl;
	std::cout << "F3: Depth Smoothing" << std::endl;
	std::cout << "F4: Thichness" << std::endl;
	std::cout << "F5: Screen Space Fluid Rendering" << std::endl;
	std::cout << "F6: Volume Rendering" << std::endl;
	std::cout << "arrow key : camera move" << std::endl;
	std::cout << "z : camera up" << std::endl;
	std::cout << "d : camera out" << std::endl;
	std::cout << "r : reset simulation" << std::endl;
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

	printUsage();

	glutMainLoop();
}