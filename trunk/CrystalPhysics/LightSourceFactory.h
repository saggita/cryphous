#ifndef __LIGHT_SOURCE_FACTORY_H__
#define __LIGHT_SOURCE_FACTORY_H__

#include "Uncopyable.h"
#include <vector>

#include "LightSource.h"

namespace Crystal{
	namespace Physics{

class LightSourceFactory : private Uncopyable
{
public:
	LightSourceFactory() :nextID( 0)
	{
	}

	~LightSourceFactory(void)
	{
		init();
	}

	void init()
	{
		for( size_t i = 0; i < lightSources.size(); ++i ) {
			delete lightSources[i];
		}
		lightSources.clear();
		this->nextID = 0;
	}


	LightSource* createLightSource( const Geom::Vector3d& center, const size_t howManyPhotons, const float velocity )
	{
		lightSources.push_back( new LightSource( nextID++, center, velocity ) );
		lightSources.back()->addPhotons( howManyPhotons );
		return lightSources.back();
	}

	LightSourceVector getLightSources() const { return lightSources; }

	PhotonVector getPhotons() const
	{
		PhotonVector results;
		for( size_t i = 0; i < lightSources.size(); ++i ) {
			const PhotonVector& photons = lightSources[i]->getPhotons();
			results.insert( results.end(), photons.begin(), photons.end() );
		}
		return results;
	}

private:
	unsigned int nextID;
	LightSourceVector lightSources;
};

	}
}

#endif