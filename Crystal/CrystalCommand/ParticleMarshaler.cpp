#include "ParticleMarshaler.h"

#include "../CrystalGeom/Vector3d.h"
#include "../CrystalPhysics/Particle.h"
#include <cassert>

using namespace Crystal::Geom;
using namespace Crystal::Physics;
using namespace Crystal::Command;

using namespace System::Collections::Generic;

List<ManagedPosition^>^ ParticleMarshaler::convertToManaged(const ParticleVector& nativeParticles)
{
	List<ManagedPosition^>^ managedPositions = gcnew List<ManagedPosition^>();
	for( size_t i = 0; i < nativeParticles.size(); ++i ) {
		ManagedPosition^ newParticle = gcnew ManagedPosition;
		newParticle->Add( nativeParticles[i]->center.getX() );
		newParticle->Add( nativeParticles[i]->center.getY() );
		newParticle->Add( nativeParticles[i]->center.getZ() );
		managedPositions->Add( newParticle );
	}

	assert( managedPositions->Count == mativeParticles.size() );
	return managedPositions;
}

std::vector<Vector3d> ParticleMarshaler::convertToNative(System::Collections::Generic::List<ManagedPosition^>^ managedPositions)
{
	std::vector<Vector3d> nativePositions;
	
	for each(ManagedPosition^ pos in managedPositions) {
		nativePositions.push_back( Vector3d( pos[0], pos[1], pos[2] ) );
	}

	assert( managedPositions->Count == mativeParticles.size() );
	return nativePositions;
}