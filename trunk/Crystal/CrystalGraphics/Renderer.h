#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <boost/noncopyable.hpp>

#include "OpenGLWrapper.h"
#include "GraphicsSettings.h"

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "Renderer.h"

#include "../CrystalPhysics/Particle.h"
#include "../CrystalPhysics/SimulationSetting.h"
#include "../CrystalPhysics/Profiler.h"
#include "../CrystalPhysics/PhysicsObjectFactory.h"
#include "../CrystalPhysics/PhysicsObject.h"

#include <boost/foreach.hpp>

#include <cassert>
#include <cmath>
#include <cstdlib>

namespace Crystal{
	namespace Graphics{

class Renderer : private boost::noncopyable
{
public:
	Renderer(const GraphicsSettings& settings) :
	  settings(settings)
	{
	}

	~Renderer()
	{
	}

	void setPictureBox( HWND pictureBoxHandle ) {
		openGLWrapper.setHandle( pictureBoxHandle );
		init();
	}

	void init() { openGLWrapper.SetCurrentRenderingContext(); }

	void rendering(Physics::PhysicsObjectFactory *factory, const int width, const int height, const Geom::Box& boundaryBox)
	{
		Physics::Profiler::get()->start("Rendering->");

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
		glTranslated( settings.cameraX, settings.cameraY, -0.1 * settings.zoom );

		glRotatef( static_cast<GLfloat>( settings.angleX ), 1.0f, 0.0f, 0.0f );
		glRotatef( static_cast<GLfloat>( settings.angleY ), 0.0f, 1.0f, 0.0f );
		glRotatef( static_cast<GLfloat>( settings.angleZ ), 0.0f, 0.0f, 1.0f );

		drawBoundaryBox(boundaryBox);

		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glDepthMask(GL_FALSE);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glPointSize( (GLfloat)(settings.pointSize) );

		glBegin(GL_POINTS);
		BOOST_FOREACH( Physics::PhysicsObject* object, factory->getPhysicsObjects() ) {
			if( object->getType() == Physics::PhysicsObject::Rigid ) {
				glColor4d( 1.0f, 1.0f, 1.0f, 1.0f );
			}
			else if( object->getType() == Physics::PhysicsObject::Obstacle ) {
				glColor4d( 0.0f, 0.0f, 0.0f, 1.0f );
			}
			else {
				const float densityRatio = object->getDensity() / 1000.0f;
				const float alpha = densityRatio * settings.pointAlpha / 100.0f; 
				glColor4f( 0.1f, 0.1f, 1.0f, alpha );
			}
			BOOST_FOREACH( Physics::Particle* particle, object->getParticles() ) {
				const Geom::Vector3d& normal = particle->normal / object->getDensity(); 
				if( normal.getLength() < 0.0005 && !particle->isIsolated() && settings.doDisplaySurface ) {
					continue;
				}
				const Geom::Vector3d& point = particle->center;
				glVertex3f( point.getX(), point.getY(), point.getZ() );
			}
		}
		glEnd();
	
		assert( glGetError() == GL_NO_ERROR );

		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
	
		glFlush();
		openGLWrapper.EndRendering();

		Physics::Profiler::get()->end("Rendering->");
	}

protected:

	void drawBoundaryBox(const Geom::Box& box)
	{
		if( !settings.drawBoundingBox ) {
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

private:
	OpenGLWrapper openGLWrapper;
	const GraphicsSettings& settings;
};

	}
}

#endif