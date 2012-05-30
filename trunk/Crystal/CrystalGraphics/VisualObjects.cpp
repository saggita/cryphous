#include "VisualObjects.h"

#include "../CrystalPhysics/PhysicsObjectFactory.h" 
#include "../CrystalPhysics/PhysicsObject.h"
#include "../CrystalPhysics/Particle.h"
#include "../CrystalPhysics/SpringParticle.h"
#include "../CrystalPhysics/SimulationSetting.h"
#include "../CrystalPhysics/Profiler.h"

#include "GraphicsSettings.h"

#include "Color4d.h"

#include "../CrystalGeom/Point3d.h"
#include "../CrystalGeom/Line.h"

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <boost/foreach.hpp>

#include <cassert>
#include <cmath>

#include "PointSprite.h"

using namespace Crystal::Geom;
using namespace Crystal::Physics;
using namespace Crystal::Graphics;

void VisualObjects::drawParticles(const ParticleVector& particles)
{
	GraphicsSettings* settings = GraphicsSettings::get();

	glColor4f( 0.1f, 0.1f, 1.0f, settings->pointAlpha / 100.0f );
	PointSprite::get()->apply();
	glBegin(GL_POINTS);
	BOOST_FOREACH( Particle* particle, particles ) {
		const Point3d& point = particle->center;
		glVertex3d( point.getX(), point.getY(), point.getZ() );
	}
	glEnd();
	PointSprite::get()->release();

	assert( glGetError() == GL_NO_ERROR );
}

void VisualObjects::drawSprings(PhysicsObjectFactory* factory)
{

	BOOST_FOREACH( PhysicsObject* object, factory->getPhysicsObjects() ) {
		if( object->getType() == PhysicsObject::Fluid || object->getType() == PhysicsObject::Cloth ) {
			continue;
		}

		glColor3f( 1.0, 1.0, 1.0);
		{
			glBegin( GL_TRIANGLE_FAN );		
			const ParticleGrid& particleGrid = object->getParticleGrid();
			const Point3d& vertexA = particleGrid.front().front().front()->center;
			const Point3d& vertexB = particleGrid.back().front().front()->center;
			const Point3d& vertexC = particleGrid.back().back().front()->center;
			const Point3d& vertexD = particleGrid.front().back().front()->center;
			glVertex3d( vertexA.getX(), vertexA.getY(), vertexA.getZ() );
			glVertex3d( vertexB.getX(), vertexB.getY(), vertexB.getZ() );
			glVertex3d( vertexC.getX(), vertexC.getY(), vertexC.getZ() );
			glVertex3d( vertexD.getX(), vertexD.getY(), vertexD.getZ() );
			glEnd();
		}
		{
			glBegin( GL_TRIANGLE_FAN );		
			const ParticleGrid& particleGrid = object->getParticleGrid();
			const Point3d& vertexA = particleGrid.front().front().back()->center;
			const Point3d& vertexB = particleGrid.back().front().back()->center;
			const Point3d& vertexC = particleGrid.back().back().back()->center;
			const Point3d& vertexD = particleGrid.front().back().back()->center;
			glVertex3d( vertexA.getX(), vertexA.getY(), vertexA.getZ() );
			glVertex3d( vertexB.getX(), vertexB.getY(), vertexB.getZ() );
			glVertex3d( vertexC.getX(), vertexC.getY(), vertexC.getZ() );
			glVertex3d( vertexD.getX(), vertexD.getY(), vertexD.getZ() );
			glEnd();
		}
		{
			glBegin( GL_TRIANGLE_FAN );		
			const ParticleGrid& particleGrid = object->getParticleGrid();
			const Point3d& vertexA = particleGrid.front().front().front()->center;
			const Point3d& vertexB = particleGrid.front().front().back()->center;
			const Point3d& vertexC = particleGrid.front().back().back()->center;
			const Point3d& vertexD = particleGrid.front().back().front()->center;
			glVertex3d( vertexA.getX(), vertexA.getY(), vertexA.getZ() );
			glVertex3d( vertexB.getX(), vertexB.getY(), vertexB.getZ() );
			glVertex3d( vertexC.getX(), vertexC.getY(), vertexC.getZ() );
			glVertex3d( vertexD.getX(), vertexD.getY(), vertexD.getZ() );
			glEnd();
		}
		{
			glBegin( GL_TRIANGLE_FAN );		
			const ParticleGrid& particleGrid = object->getParticleGrid();
			const Point3d& vertexA = particleGrid.back().front().front()->center;
			const Point3d& vertexB = particleGrid.back().front().back()->center;
			const Point3d& vertexC = particleGrid.back().back().back()->center;
			const Point3d& vertexD = particleGrid.back().back().front()->center;
			glVertex3d( vertexA.getX(), vertexA.getY(), vertexA.getZ() );
			glVertex3d( vertexB.getX(), vertexB.getY(), vertexB.getZ() );
			glVertex3d( vertexC.getX(), vertexC.getY(), vertexC.getZ() );
			glVertex3d( vertexD.getX(), vertexD.getY(), vertexD.getZ() );
			glEnd();
		}

		{
			glBegin( GL_TRIANGLE_FAN );		
			const ParticleGrid& particleGrid = object->getParticleGrid();
			const Point3d& vertexA = particleGrid.front().front().front()->center;
			const Point3d& vertexB = particleGrid.front().front().back()->center;
			const Point3d& vertexC = particleGrid.back().front().back()->center;
			const Point3d& vertexD = particleGrid.back().front().front()->center;
			glVertex3d( vertexA.getX(), vertexA.getY(), vertexA.getZ() );
			glVertex3d( vertexB.getX(), vertexB.getY(), vertexB.getZ() );
			glVertex3d( vertexC.getX(), vertexC.getY(), vertexC.getZ() );
			glVertex3d( vertexD.getX(), vertexD.getY(), vertexD.getZ() );
			glEnd();
		}

		{
			glBegin( GL_TRIANGLE_FAN );		
			const ParticleGrid& particleGrid = object->getParticleGrid();
			const Point3d& vertexA = particleGrid.front().back().front()->center;
			const Point3d& vertexB = particleGrid.front().back().back()->center;
			const Point3d& vertexC = particleGrid.back().back().back()->center;
			const Point3d& vertexD = particleGrid.back().back().front()->center;
			glVertex3d( vertexA.getX(), vertexA.getY(), vertexA.getZ() );
			glVertex3d( vertexB.getX(), vertexB.getY(), vertexB.getZ() );
			glVertex3d( vertexC.getX(), vertexC.getY(), vertexC.getZ() );
			glVertex3d( vertexD.getX(), vertexD.getY(), vertexD.getZ() );
			glEnd();
		}
	}
}