#include "SpringParticleFactory.h"

#include "SpringParticle.h"
#include "Particle.h"

#include "../CrystalGeom/Line.h"

#include <boost/foreach.hpp>

#include <cassert>

using namespace Crystal::Physics;
using namespace Crystal::Geom;

SpringParticleFactory::SpringParticleFactory(const ParticleVector& particles, const int uNumber, const int vNumber, const int wNumber) :
uNumber( uNumber),
	vNumber( vNumber),
	wNumber( wNumber)
{
	createSpringParticles( particles );
}

SpringParticleFactory::~SpringParticleFactory(void)
{
	BOOST_FOREACH( SpringParticle* springParticle, springParticles ) {
		delete springParticle;
	}
}

void SpringParticleFactory::createSpringParticles(const ParticleVector& particles)
{
	assert( !particles.empty() );
	//assert( particles.size() == (uNumber * vNumber) );

	// ó±éqÇ3éüå≥îzóÒÇ…ï€éùÇµÇ»Ç®Ç∑.
	//std::vector< std::vector< std::vector< Particle* > > > particleGrid;
	ParticleVector::const_iterator iter = particles.begin();
	for( int u = 0; u < uNumber; ++u ) {
		particleGrid.push_back( std::vector< std::vector< Particle* > >() );
		for( int v = 0; v < vNumber; ++v ) {
			particleGrid[u].push_back( std::vector< Particle* >() );
			for( int w = 0; w < wNumber; ++w ) {
				particleGrid[u][v].push_back( *iter );
				iter++;
			}
		}
	}

	for( int u = 0; u < uNumber; ++u ) {
		for( int v = 0; v < vNumber; ++v ) { 
			for( int w = 0; w < wNumber; ++w ) {
				Particle* uPlus =  ( u == uNumber-1) ? 0 : particleGrid[u+1][v][w];
				Particle* vPlus = ( v == vNumber-1) ? 0 : particleGrid[u][v+1][w];
				Particle* wPlus = ( w == wNumber-1) ? 0 : particleGrid[u][v][w+1];
				SpringParticle* grid = new SpringParticle( particleGrid[u][v][w], uPlus, vPlus, wPlus );
				springParticles.push_back( grid );
			}
		}
	}
}

LineList SpringParticleFactory::getLines() const
{
	LineList lines;
	BOOST_FOREACH( SpringParticle* springParticle, springParticles ) {
		lines.splice( lines.end(), springParticle->getLines() );
	}
	return lines;
}

std::vector<Particle*> SpringParticleFactory::getCorners() const
{
	std::vector<Particle*> corners;
	corners.push_back( getParticleGrid()[0][0][0] );
	corners.push_back( getParticleGrid()[0][vNumber-1][0]);
	corners.push_back( getParticleGrid()[0][vNumber-1][wNumber-1]);
	corners.push_back( getParticleGrid()[0][0][wNumber-1]);
	corners.push_back( getParticleGrid()[uNumber-1][0][0]);
	corners.push_back( getParticleGrid()[uNumber-1][vNumber-1][0]);
	corners.push_back( getParticleGrid()[uNumber-1][vNumber-1][wNumber-1]);
	corners.push_back( getParticleGrid()[uNumber-1][0][wNumber-1]);
	return corners;
}