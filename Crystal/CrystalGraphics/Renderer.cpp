#include "../External/glee/GLee.h"

#include "Renderer.h"

#include "TextureCreator.h"
#include "GraphicsSettings.h"
#include "Color4d.h"
#include "VisualObjects.h"

#include "../CrystalPhysics/Particle.h"
#include "../CrystalPhysics/SimulationSetting.h"
#include "../CrystalPhysics/Profiler.h"

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

void Renderer::rendering(const ParticleVector& particles, const int width, const int height)
{
	Profiler::get()->start("RenderingTotal");

	glClearColor( 0.5f, 0.5f, 0.9f, 1.0f );
	openGLWrapper.BeginRendering();

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glViewport(0, 0, width, height);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	const float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
	gluPerspective( 40, aspectRatio, 0.01, 10.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslated( GraphicsSettings::get()->cameraX, GraphicsSettings::get()->cameraY, -0.1 * GraphicsSettings::get()->zoom );

	glRotatef( static_cast<GLfloat>( GraphicsSettings::get()->angleX ), 1.0f, 0.0f, 0.0f );
	glRotatef( static_cast<GLfloat>( GraphicsSettings::get()->angleY ), 0.0f, 1.0f, 0.0f );
	glRotatef( static_cast<GLfloat>( GraphicsSettings::get()->angleZ ), 0.0f, 0.0f, 1.0f );

	glEnable(GL_BLEND);
	glDepthMask(GL_FALSE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPointSize( (GLfloat)(GraphicsSettings::get()->pointSize) );

	drawBoundaryBox();

	VisualObjects visualObjects;
	visualObjects.drawParticles(particles);

	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);

	visualObjects.drawSprings();
	
	glFlush();
	openGLWrapper.EndRendering();

	Profiler::get()->end("RenderingTotal");
}

void Renderer::drawBoundaryBox()
{
	if( !GraphicsSettings::get()->drawBoundingBox ) {
		return;
	}
	const Box& box = SimulationSetting::get()->boundaryBox;

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