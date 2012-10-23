#ifndef __SEARCH_PHOTON_FACTORY_H__
#define __SEARCH_PHOTON_FACTORY_H__

#include <vector>
#include <algorithm>
#include "SearchPhoton.h"
#include "Photon.h"

namespace Crystal{
	namespace Physics{
		
class SearchPhotonFactory
{
public:

	SearchPhotonFactory(){};

	SearchPhotonFactory(const PhotonVector& photons, const float effectLength) { addPhotons( photons, effectLength ); }

	~SearchPhotonFactory(void){};

	void init() { searchPhotons.clear(); }

	void addPhotons(const PhotonVector& photons, const float effectLength)
	{
		for( size_t i = 0; i < photons.size(); ++i ) {
			searchPhotons.push_back( SearchPhoton( photons[i], effectLength) );
		}
		std::sort( searchPhotons.begin(), searchPhotons.end() );
		return;
	}

	SearchPhotonVector getSearchPhotons() const { return searchPhotons; }

	PhotonVector getPhotons() const
	{
		PhotonVector photons;
		for( size_t i = 0; i < searchPhotons.size(); ++i ) {
			photons.push_back( searchPhotons[i].getPhoton() );
		}
		return photons;
	}

private:
	SearchPhotonVector searchPhotons;
};

	}
}

#endif