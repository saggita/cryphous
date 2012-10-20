#include "Renderer.h"

#include "../CrystalPhysics/Uncopyable.h"
#include "../CrystalPhysics/Particle.h"
#include "../CrystalPhysics/SimulationSetting.h"
#include "../CrystalPhysics/Profiler.h"
#include "../CrystalPhysics/PhysicsObjectFactory.h"
#include "../CrystalPhysics/PhysicsObject.h"
#include "../CrystalPhysics/LightSourceFactory.h"
#include "PointSprite.h"

#include <cassert>
#include <cmath>
#include <cstdlib>

using namespace Crystal::Graphics;
using namespace Crystal::Physics;
using namespace Crystal::Geom;

void Renderer::rendering(PhysicsObjectFactory *factory, LightSourceFactory* lightSourceFactory, const int width, const int height, const Box& boundaryBox)
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
		gluPerspective( 40, aspectRatio, 0.01, 10000.0);

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

		PointSprite::get()->apply();
		glBegin(GL_POINTS);
		const Physics::PhysicsObjectVector& objects = factory->getPhysicsObjects();
		for( Physics::PhysicsObjectVector::const_iterator iter = objects.begin(); iter != objects.end(); ++iter ) {
			Physics::PhysicsObject* object = (*iter);
			if( object->getType() == Physics::PhysicsObject::Rigid ) {
				glColor4d( 1.0f, 1.0f, 1.0f, 1.0f );
			}
			else if( object->getType() == Physics::PhysicsObject::Obstacle ) {
				glColor4d( 0.0f, 0.0f, 0.0f, 1.0f );
			}
			else{
				const float densityRatio = object->getDensity() / 1000.0f;
				const float alpha = densityRatio * settings.pointAlpha / 100.0f; 
				glColor4f( 0.1f, 0.1f, 1.0f, alpha );
			}
			const Physics::ParticleVector& particles = object->getParticles();
			for( size_t i = 0; i < particles.size(); ++i ) {
				const Geom::Vector3d& point = particles[i]->center;
				glVertex3f( point.getX(), point.getY(), point.getZ() );
			}
		}
		const float alpha = settings.pointAlpha / 100.0f;
		glColor4d( 1.0f, 1.0f, 1.0f, alpha );
		const PhotonVector& photons = lightSourceFactory->getPhotons();
		for( size_t i = 0; i < photons.size(); ++i ) {
			if( !photons[i]->velocity.isZero() ) {
				continue;
			}
			const Geom::Vector3d& point = photons[i]->center;
			glVertex3f( point.getX(), point.getY(), point.getZ() );
		}
		glEnd();
		PointSprite::get()->release();

		glLineWidth( static_cast<GLfloat>(settings.lineSize) );
		for( Physics::PhysicsObjectVector::const_iterator iter = objects.begin(); iter != objects.end(); ++iter ) {
			Physics::PhysicsObject* object = (*iter);
			if( object->getType() == Physics::PhysicsObject::Elastic ) {
				glBegin(GL_LINE_STRIP);
				const float densityRatio = object->getDensity() / 1000.0f;
				const float alpha = densityRatio * settings.lineAlpha / 100.0f; 
				glColor4f( 0.0f, 0.0f, 0.0f, alpha );
				const Physics::ParticleVector& particles = object->getParticles();
				for( size_t i = 0; i < particles.size(); ++i ) {
					const Geom::Vector3d& point = particles[i]->center;
					glVertex3f( point.getX(), point.getY(), point.getZ() );
				}
				glEnd();
			}
		}
	
		assert( glGetError() == GL_NO_ERROR );

		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
	
		glFlush();
		openGLWrapper.EndRendering();

		Physics::Profiler::get()->end("Rendering->");
}

void Renderer::drawBoundaryBox(const Box& box)
{
		if( !settings.drawBoundingBox ) {
			return;
		}
	
		glPushMatrix();

		glColor4d( 0.0, 0.0, 0.0, 1.0 );

		glLineWidth(1.0f);

		glColor4d( 1.0, 0.0, 0.0, 1.0 );
		glBegin(GL_TRIANGLE_STRIP);
			glVertex3d( box.getMinX(), box.getMinY(), box.getMinZ() );
			glVertex3d( box.getMaxX(), box.getMinY(), box.getMinZ() );
			glVertex3d( box.getMinX(), box.getMaxY(), box.getMinZ() );
			glVertex3d( box.getMaxX(), box.getMaxY(), box.getMinZ() );
		glEnd();

		glColor4d( 0.0, 1.0, 0.0, 1.0 );
		glBegin(GL_TRIANGLE_STRIP);
			glVertex3d( box.getMinX(), box.getMinY(), box.getMaxZ() );
			glVertex3d( box.getMaxX(), box.getMinY(), box.getMaxZ() );
			glVertex3d( box.getMinX(), box.getMaxY(), box.getMaxZ() );
			glVertex3d( box.getMaxX(), box.getMaxY(), box.getMaxZ() );
		glEnd();

		glColor4d( 0.0, 0.0, 1.0, 1.0 );
		glBegin(GL_TRIANGLE_STRIP);
			glVertex3d( box.getMinX(), box.getMinY(), box.getMinZ() );
			glVertex3d( box.getMinX(), box.getMaxY(), box.getMinZ() );
			glVertex3d( box.getMinX(), box.getMinY(), box.getMaxZ() );
			glVertex3d( box.getMinX(), box.getMaxY(), box.getMaxZ() );
		glEnd();

		glColor4d( 0.0, 0.0, 0.0, 1.0 );
		glBegin(GL_TRIANGLE_STRIP);
			glVertex3d( box.getMaxX(), box.getMinY(), box.getMinZ() );
			glVertex3d( box.getMaxX(), box.getMaxY(), box.getMinZ() );
			glVertex3d( box.getMaxX(), box.getMinY(), box.getMaxZ() );
			glVertex3d( box.getMaxX(), box.getMaxY(), box.getMaxZ() );
		glEnd();

		glPopMatrix();
}