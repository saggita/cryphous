#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "Renderer.h"

#include "GraphicsSettings.h"

#include "../CrystalPhysics/Particle.h"
#include "../CrystalPhysics/SimulationSetting.h"
#include "../CrystalPhysics/Profiler.h"
#include "../CrystalPhysics/PhysicsObjectFactory.h"
#include "../CrystalPhysics/PhysicsObject.h"

#include <boost/foreach.hpp>

#include <cassert>
#include <cmath>
#include <cstdlib>


using namespace Crystal::Geom;
using namespace Crystal::Physics;
using namespace Crystal::Graphics;

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::init()
{
	openGLWrapper.SetCurrentRenderingContext();
}

void Renderer::rendering(PhysicsObjectFactory *factory, const int width, const int height, const Box& boundaryBox)
{
	Profiler::get()->start("Rendering->");

	glClearColor( 0.8f, 0.8f, 0.9f, 1.0f );
	openGLWrapper.BeginRendering();

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glViewport(0, 0, width, height);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	const float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
	gluPerspective( 40, aspectRatio, 0.01, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslated( GraphicsSettings::get()->cameraX, GraphicsSettings::get()->cameraY, -0.1 * GraphicsSettings::get()->zoom );

	glRotatef( static_cast<GLfloat>( GraphicsSettings::get()->angleX ), 1.0f, 0.0f, 0.0f );
	glRotatef( static_cast<GLfloat>( GraphicsSettings::get()->angleY ), 0.0f, 1.0f, 0.0f );
	glRotatef( static_cast<GLfloat>( GraphicsSettings::get()->angleZ ), 0.0f, 0.0f, 1.0f );

	drawBoundaryBox(boundaryBox);

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glDepthMask(GL_FALSE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPointSize( (GLfloat)(GraphicsSettings::get()->pointSize) );

	glBegin(GL_POINTS);
	BOOST_FOREACH( Particle* particle, factory->getSortedParticles() ) {
		const Vector3d& point = particle->center;
		if( particle->getParent()->getType() == PhysicsObject::Rigid ) {
			glColor4d( 1.0f, 1.0f, 1.0f, 1.0f );
			glVertex3d( point.getX(), point.getY(), point.getZ() );
		}
		else if( particle->getParent()->getType() == PhysicsObject::Obstacle ) {
			glColor4d( 0.0f, 0.0f, 0.0f, 1.0f );
			glVertex3d( point.getX(), point.getY(), point.getZ() );
		}
		else {
			const float densityRatio = particle->density / 1000.0f;
			const float alpha = densityRatio * GraphicsSettings::get()->pointAlpha / 100.0f; 
			glColor4f( 0.1f, 0.1f, 1.0f, alpha );
			glVertex3f( point.getX(), point.getY(), point.getZ() );
		}
	}
	glEnd();
	
	assert( glGetError() == GL_NO_ERROR );

	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	
	glFinish();//glFlush();
	openGLWrapper.EndRendering();

	Profiler::get()->end("Rendering->");
}

void Renderer::drawBoundaryBox(const Box& box)
{
	if( !GraphicsSettings::get()->drawBoundingBox ) {
		return;
	}
	
	glPushMatrix();

	glColor4d( 0.0, 0.0, 0.0, 1.0 );

	glBegin(GL_LINE_LOOP);
		glVertex3d( box.getMinX(), box.getMinY(), box.getMinZ() );
		glVertex3d( box.getMaxX(), box.getMinY(), box.getMinZ() );
		glVertex3d( box.getMaxX(), box.getMaxY(), box.getMinZ() );
		glVertex3d( box.getMinX(), box.getMaxY(), box.getMinZ() );
	glEnd();

	glBegin(GL_LINE_LOOP);
		glVertex3d( box.getMinX(), box.getMinY(), box.getMaxZ() );
		glVertex3d( box.getMaxX(), box.getMinY(), box.getMaxZ() );
		glVertex3d( box.getMaxX(), box.getMaxY(), box.getMaxZ() );
		glVertex3d( box.getMinX(), box.getMaxY(), box.getMaxZ() );
	glEnd();

	glBegin(GL_LINE_LOOP);
		glVertex3d( box.getMinX(), box.getMinY(), box.getMinZ() );
		glVertex3d( box.getMinX(), box.getMaxY(), box.getMinZ() );
		glVertex3d( box.getMinX(), box.getMaxY(), box.getMaxZ() );
		glVertex3d( box.getMinX(), box.getMinY(), box.getMaxZ() );
	glEnd();

	glBegin(GL_LINE_LOOP);
		glVertex3d( box.getMaxX(), box.getMinY(), box.getMinZ() );
		glVertex3d( box.getMaxX(), box.getMaxY(), box.getMinZ() );
		glVertex3d( box.getMaxX(), box.getMaxY(), box.getMaxZ() );
		glVertex3d( box.getMaxX(), box.getMinY(), box.getMaxZ() );
	glEnd();

	glPopMatrix();
}